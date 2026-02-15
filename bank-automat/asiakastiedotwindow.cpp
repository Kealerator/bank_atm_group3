#include "asiakastiedotwindow.h"
#include "ui_asiakastiedotwindow.h"
#include "environment.h"

asiakastiedotwindow::asiakastiedotwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::asiakastiedotwindow)
{
    ui->setupUi(this);
    connect(ui->btnReturn, &QPushButton::clicked, this, &::asiakastiedotwindow::btnReturnSlot);
    manager = new QNetworkAccessManager(this);
}

asiakastiedotwindow::~asiakastiedotwindow()
{
    delete ui;
}

void asiakastiedotwindow::setIdTili(int newIdTili)
{
    idTili = newIdTili;
}

void asiakastiedotwindow::requestAsiakastiedot()
{
    qDebug() << "idTili:" << idTili;

    QString base_url =Environment::base_url()+"asiakas/tiedot/" + QString::number(idTili);
    QNetworkRequest request(base_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer " + token.toUtf8());


    reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, &asiakastiedotwindow::asiakastiedotSlot);
}

void asiakastiedotwindow::setToken(const QString &newToken)
{
    token = newToken;
}

void asiakastiedotwindow::btnReturnSlot()
{
this->close();
}

void asiakastiedotwindow::asiakastiedotSlot()
{
    QByteArray response = reply->readAll();
    qDebug() << "Asiakastiedot:" << response;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
    QJsonArray jsonArray = jsonDoc.array();
    QJsonObject jsonObject = jsonArray.at(0).toObject();

    ui->labelFname->setText(jsonObject["etunimi"].toString());
    ui->labelLname->setText(jsonObject["sukunimi"].toString());
    ui->labelAddress->setText(jsonObject["osoite"].toString());
    ui->labelPnumber->setText(jsonObject["puhelinnumero"].toString());

    reply->deleteLater();
}
