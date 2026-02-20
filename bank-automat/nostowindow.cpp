#include "nostowindow.h"
#include "ui_nostowindow.h"
#include "environment.h"

NostoWindow::NostoWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NostoWindow)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);

    inaktiivisuusAjastin = new QTimer(this);
    inaktiivisuusAjastin->setInterval(10000);
    connect(inaktiivisuusAjastin, &QTimer::timeout, this, &NostoWindow::aikakatkaisu);
    inaktiivisuusAjastin->start();

    connect(manager, &QNetworkAccessManager::finished, this, &NostoWindow::vastaus);
    connect(ui->btnReturn, &QPushButton::clicked, this, &NostoWindow::btnTakaisinSlot);

    connect (ui->btn20, &QPushButton::clicked, this, &NostoWindow::nosta20);
    connect (ui->btn40, &QPushButton::clicked, this, &NostoWindow::nosta40);
    connect (ui->btn50, &QPushButton::clicked, this, &NostoWindow::nosta50);
    connect (ui->btn80, &QPushButton::clicked, this, &NostoWindow::nosta80);
    connect (ui->btn100, &QPushButton::clicked, this, &NostoWindow::nosta100);
    connect (ui->btn200, &QPushButton::clicked, this, &NostoWindow::nosta200);
    connect(ui->btnNostaMuu, &QPushButton::clicked, this, &NostoWindow::nostaMuuSumma);

    connect(ui->btn20, &QPushButton::clicked, this, &NostoWindow::nollaaAjastin);
    connect(ui->btn40, &QPushButton::clicked, this, &NostoWindow::nollaaAjastin);
    connect(ui->btn50, &QPushButton::clicked, this, &NostoWindow::nollaaAjastin);
    connect(ui->btn80, &QPushButton::clicked, this, &NostoWindow::nollaaAjastin);
    connect(ui->btn100, &QPushButton::clicked, this, &NostoWindow::nollaaAjastin);
    connect(ui->btn200, &QPushButton::clicked, this, &NostoWindow::nollaaAjastin);
    connect(ui->btnNostaMuu, &QPushButton::clicked, this, &NostoWindow::nollaaAjastin);
}

NostoWindow::~NostoWindow()
{
    delete ui;
}

void NostoWindow::setToken(const QString &newToken)
{
    token = newToken;
}


void NostoWindow::btnTakaisinSlot()
{
    this->hide();
}

void NostoWindow::vastaus(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    QJsonObject obj = QJsonDocument::fromJson(data).object();

    if (reply->error() != QNetworkReply::NoError) {
        ui->labelStatus->setText("Verkkovirhe");
        reply->deleteLater();
        return;
    }


    if (obj.contains("success") && !obj["success"].toBool()) {

        QString viesti = obj["message"].toString();
        QString teksti = "Virhe: " + viesti;


        if (obj.contains("saldo")) {
            double saldo = obj["saldo"].toDouble();
            teksti += "\nSaldo: " + QString::number(saldo);
        }


        if (obj.contains("käytettävissä")) {
            double kaytettavissa = obj["käytettävissä"].toDouble();
            teksti += "\nKäytettävissä: " + QString::number(kaytettavissa);
        }

        ui->labelStatus->setText(teksti);
        reply->deleteLater();
        return;
    }


    QString viesti = obj["message"].toString();
    QString teksti = viesti;

    if (obj.contains("uusiSaldo")) {
        double saldo = obj["uusiSaldo"].toDouble();
        teksti += "\nSaldo: " + QString::number(saldo);
    }

    if (obj.contains("käytettävissä")) {
        double kaytettavissa = obj["käytettävissä"].toDouble();
        teksti += "\nKäytettävissä: " + QString::number(kaytettavissa);
    }

    ui->labelStatus->setText(teksti);
    reply->deleteLater();
}

void NostoWindow::nosta20()
{
    lahetaNostoPyynto(20);
}

void NostoWindow::nosta40()
{
    lahetaNostoPyynto(40);
}

void NostoWindow::nosta50()
{
    lahetaNostoPyynto(50);
}

void NostoWindow::nosta80()
{
    lahetaNostoPyynto(80);
}

void NostoWindow::nosta100()
{
    lahetaNostoPyynto(100);
}

void NostoWindow::nosta200()
{
    lahetaNostoPyynto(200);
}

void NostoWindow::nostaMuuSumma()
{
    QString muuSumma = ui->lineEditMuuSumma->text();

    if (muuSumma.isEmpty()) {
        ui->labelStatus->setText("Syötä nostettava summa");
        return;
    }

    int summa = muuSumma.toInt();

    if (summa <= 0) {
        ui->labelStatus->setText("Virheellinen summa");
        return;
    }

    lahetaNostoPyynto(summa);
}

void NostoWindow::aikakatkaisu()
{
    inaktiivisuusAjastin->stop();

    this->close();

}

void NostoWindow::nollaaAjastin()
{
    inaktiivisuusAjastin->start();
}



int NostoWindow::getIdtili() const
{
    return idtili;
}

void NostoWindow::setIdtili(int newIdtili)
{
    idtili = newIdtili;
}


void NostoWindow::lahetaNostoPyynto(int summa)
{
    qDebug() << "NostoWindow idtili =" << idtili;
    QString url = Environment::base_url()+"nosto/" + QString::number(idtili);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer " + token.toUtf8());
    QByteArray body = QString("{\"summa\": %1}").arg(summa).toUtf8();
    manager->post(request, body);
}

