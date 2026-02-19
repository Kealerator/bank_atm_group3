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
    connect(ui->btnPoistu, &QPushButton::clicked, this, &tilitapahtumatwindow::btnPoistuslot);
   // connect(ui->btnVasen, &QPushButton::clicked, this &tilitapahtumatwindow::btnVasenSlot);
    //connect(ui->btnOikea, &QPushButton::clicked, this &tilitapahtumatwindow::btnOikeaSlot);
}

tilitapahtumatwindow::~tilitapahtumatwindow()
{
    delete ui;
}

void tilitapahtumatwindow::btnTapahtumatClicked()
{
    QString url =Environment::base_url()+"tilitapahtumat/tili/"+QString::number(idtili);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer " + token.toUtf8());
    reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &tilitapahtumatwindow::Tilitapahtumatslot);

}

void tilitapahtumatwindow::Tilitapahtumatslot()
{
    QByteArray response = reply->readAll();
    qDebug() << "Tilitapahtumat: " << response;

    QJsonDocument json_doc = QJsonDocument::fromJson(response);
    QJsonArray json_array=json_doc.array();

    QVector<tilitapahtumat> listTilitapahtumat;
    for (const QJsonValue &value : json_array) {
        if (value.isObject()) {
            tilitapahtumat tilitapahtuma = tilitapahtumat::mapJson(value.toObject());
            listTilitapahtumat.append(tilitapahtuma);
        }
    }
    if (listTilitapahtumat.size() > 10) {
        listTilitapahtumat = QVector<tilitapahtumat>(listTilitapahtumat.end() -10, listTilitapahtumat.end());
    }

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
    reply->deleteLater();
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
{
    this->parentWidget()->show();
    this->close();
}

void tilitapahtumatwindow::btnVasenSlot()
{

}

void tilitapahtumatwindow::btnOikeaSlot()
{

}

