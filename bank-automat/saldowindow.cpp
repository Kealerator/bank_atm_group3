#include "saldowindow.h"
#include "ui_saldowindow.h"
#include "environment.h"

saldowindow::saldowindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::saldowindow)
{
    ui->setupUi(this);
    connect(ui->btnReturn, &QPushButton::clicked, this, &::saldowindow::btnReturnSlot);
    manager = new QNetworkAccessManager(this);


}

void saldowindow::setIdTili(int newIdTili)
{
    idTili = newIdTili;
}

void saldowindow::requestSaldo(){
    qDebug() << "idTili:" << idTili;

    QString base_url =Environment::base_url()+"tili/saldo/" + QString::number(idTili);
    QNetworkRequest request(base_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer " + token.toUtf8());

    reply = manager->get(request);

   connect(reply, &QNetworkReply::finished, this, &saldowindow::saldoSlot);
}



void saldowindow::setToken(const QString &newToken)
{
    token = newToken;
}

saldowindow::~saldowindow()
{
    delete ui;
}

void saldowindow::saldoSlot()
{
    QByteArray response = reply->readAll();
    qDebug() << "Saldotiedot:" << response;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
    QJsonArray jsonArray = jsonDoc.array();
    QJsonObject jsonObject = jsonArray.at(0).toObject();
    ui->labelFname->setText(jsonObject["etunimi"].toString());
    ui->labelLname->setText(jsonObject["sukunimi"].toString());
    ui->labelSaldo->setText(QString::number(jsonObject["saldo"].toString().toDouble(),'f', 2));

    reply->deleteLater();
}





void saldowindow::btnReturnSlot(){
    this->close();
}




