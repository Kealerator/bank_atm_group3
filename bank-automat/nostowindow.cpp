#include "nostowindow.h"
#include "ui_nostowindow.h"
#include "environment.h"

NostoWindow::NostoWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NostoWindow)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &NostoWindow::vastaus);
    connect(ui->btnTakaisin, &QPushButton::clicked, this, &NostoWindow::btnTakaisinSlot);
    connect (ui->btn20, &QPushButton::clicked, this, &NostoWindow::nosta20);
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
    this->parentWidget()->show();
    this->close();
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

