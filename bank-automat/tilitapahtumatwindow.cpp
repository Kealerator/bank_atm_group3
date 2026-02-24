#include "tilitapahtumatwindow.h"
#include "ui_tilitapahtumatwindow.h"
#include "environment.h"
#include <QStandardItemModel>

tilitapahtumatwindow::tilitapahtumatwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::tilitapahtumatwindow)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);

    //Alustetaan ajastin
    inaktiivisuusAjastin = new QTimer(this);
    inaktiivisuusAjastin->setInterval(10000); //Asetetaan ajastin 10 sekuntiin
    connect(inaktiivisuusAjastin, QTimer::timeout, this, &tilitapahtumatwindow::aikakatkaisu);
    inaktiivisuusAjastin->start();



    connect(ui->btnReturn, &QPushButton::clicked, this, &tilitapahtumatwindow::btnPoistuslot);
    connect(ui->btnOikea, &QPushButton::clicked, this, &tilitapahtumatwindow::btnOikeaSlot);
    connect(ui->btnVasen, &QPushButton::clicked, this, &tilitapahtumatwindow::btnVasenSlot);
}

tilitapahtumatwindow::~tilitapahtumatwindow()
{
    delete ui;
}

void tilitapahtumatwindow::btnTapahtumatClicked()
{   // Käsittelee tilitpahtumien napautuksia

    QString url =Environment::base_url()+"tilitapahtumat/tili/"+QString::number(idtili);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer " + token.toUtf8());
    reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &tilitapahtumatwindow::Tilitapahtumatslot);

}


void tilitapahtumatwindow::Tilitapahtumatslot()
{   //Käsitelee saapuneet tilitapahtumat
    QByteArray response = reply->readAll();
    qDebug() << "Tilitapahtumat: " << response;

    QJsonDocument json_doc = QJsonDocument::fromJson(response);
    QJsonArray json_array=json_doc.array();

    //QVector<tilitapahtumat> kaikkitilitapahtumat;
    kaikkitilitapahtumat.clear();
    for (const QJsonValue &value : json_array) {
        if (value.isObject()) {
            tilitapahtumat tilitapahtuma = tilitapahtumat::mapJson(value.toObject());
            kaikkitilitapahtumat.append(tilitapahtuma);
            }
        }

    listTilitapahtumat=kaikkitilitapahtumat; // Määrittä sen listan
    nykyinenIndeksi = 0; //Nollataan indeksi
    näytäSivu(); // Näyttää ensinmäisen sivun datasta
    reply->deleteLater();
}

void tilitapahtumatwindow::näytäSivu()
{
    //Näytä data taulukossa
    qDebug("Näytäsivu");
    qDebug()<<"Indeksi nyt: " << nykyinenIndeksi;

    int end = nykyinenIndeksi + 10;

    qDebug()<<"Listan koko: " << listTilitapahtumat.size();
    qDebug()<<"Indeksi nyt: " << nykyinenIndeksi;

    if (end > listTilitapahtumat.size()) {
        end = listTilitapahtumat.size();
    }

    // tämä tai

    // int end = qMin(nykyinenIndeksi + 10, listTilitapahtumat.size());

    qDebug("Lista");
    qDebug()<<"Indeksi nyt: " << nykyinenIndeksi;
    qDebug()<<"Listan koko: " << listTilitapahtumat.size();

    listTilitapahtumat = listTilitapahtumat.mid(nykyinenIndeksi, 10); // Rajaa listan kymmeneen tilitapahtumaan

    qDebug("Lista part 2");
    qDebug()<<"Indeksi nyt: " << nykyinenIndeksi;
    qDebug()<<"Listan koko: " << listTilitapahtumat.size();

    auto *tableModel = new QStandardItemModel(listTilitapahtumat.size(), 4, this);
    tableModel->setHorizontalHeaderLabels({ tr("tilinumero"), tr("tapahtumat"), tr("summa"), tr("ajankohta") });
    for (int row = 0; row<listTilitapahtumat.size(); ++row){
        const tilitapahtumat &tilitapahtuma = listTilitapahtumat[row];
        tableModel->setItem(row, 0, new QStandardItem(tilitapahtuma.tilinumero));
        tableModel->setItem(row, 1, new QStandardItem(tilitapahtuma.tapahtumat));
        tableModel->setItem(row, 2, new QStandardItem(QString::number(tilitapahtuma.summa)));
        tableModel->setItem(row, 3, new QStandardItem(tilitapahtuma.ajankohta));
    }
    ui->tilitapahtumatTable->setModel(tableModel);
    ui->tilitapahtumatTable->verticalHeader()->setVisible(false);
    ui->tilitapahtumatTable->resizeColumnsToContents();

    qDebug("Kun pöytä on luotu");
    qDebug()<<"Listan koko: " << listTilitapahtumat.size();
    qDebug()<<"Indeksi nyt: " << nykyinenIndeksi;

    //Rajoittimet, että vasen nappia ei voi painaa vielä, kunnes oikea nappia on ensinmäisenä painettu
    //ui->btnVasen->setEnabled(nykyinenIndeksi > 0);
    //ui->btnOikea->setEnabled(nykyinenIndeksi + 10 < listTilitapahtumat.size());
}

void tilitapahtumatwindow::setToken(const QString &newToken)
{
    token = newToken;
}

void tilitapahtumatwindow::setIdtili(int newIdtili)
{
    idtili = newIdtili;
}

void tilitapahtumatwindow::btnPoistuslot()
{   // Käyttäjä nappia painatessa poistuu tapahtumat ikkunasta

    qDebug("Poistu");

    this->parentWidget()->show();
    this->close();
}

void tilitapahtumatwindow::btnVasenSlot()

{   //Vähentää seuraavat kymmenen tilitapahtumaa taulusta vähentämällä indeksiä

    qDebug("Vasen nappi");
    qDebug()<<"Indeksi nyt: " << nykyinenIndeksi;
    qDebug()<<"Listan koko: " << listTilitapahtumat.size();

    nollaaAjastin();
    if (nykyinenIndeksi - 10 >= 0) {
        nykyinenIndeksi -= 10; //Pienennä indeksiä

        qDebug()<<"Indeksi nyt: " << nykyinenIndeksi;

        näytäSivu();

        qDebug()<<"Listan koko: " << listTilitapahtumat.size();

    }
}

void tilitapahtumatwindow::btnOikeaSlot()

{   //Lisää kymmenen seuraavaa tilitapahtumaa tauluun nostaen indeksiä

    qDebug("Oikea nappi");
    qDebug()<<"Indeksi nyt: " << nykyinenIndeksi;
    qDebug()<<"Listan koko: " << listTilitapahtumat.size();

    nollaaAjastin();
    if (nykyinenIndeksi + 10 <listTilitapahtumat.size()) {
        nykyinenIndeksi += 10; // Kasvata indeksiä
        näytäSivu();

        qDebug()<<"Listan koko: " << listTilitapahtumat.size();
        qDebug()<<"Indeksi nyt: " << nykyinenIndeksi;

    }
}

void tilitapahtumatwindow::aikakatkaisu()
{
    inaktiivisuusAjastin->stop();
    token.clear();
    this->hide();

    QWidget *parent = parentWidget();
    if (parent)
        parent->show();
}

void tilitapahtumatwindow::nollaaAjastin()
{
    inaktiivisuusAjastin->start();
}

