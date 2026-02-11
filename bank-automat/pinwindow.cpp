#include "pinwindow.h"
#include "ui_pinwindow.h"
#include "QDebug"
#include "mainmenu.h"
#include <QMessageBox>

PINWindow::PINWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PINWindow)
{
    ui->setupUi(this);
    connect(ui->btnSignIn, &QPushButton::clicked, this, &PINWindow::btnSignInSlot);


    manager = new QNetworkAccessManager(this);
    timerId = startTimer(1000);
    ui->linePIN->setFocus();

}

PINWindow::~PINWindow()
{
    killTimer(timerId);
    delete ui;
}

QString PINWindow::getTunniste() const
{
    return tunniste;
}

void PINWindow::setTunniste(const QString &newTunniste)
{
    tunniste = newTunniste;
}

QString PINWindow::getPin() const
{
    return pin;
}

void PINWindow::setPin(const QString &newPin)
{
    pin = newPin;
}

bool PINWindow::checkPINFormat(QString string)
{
    if(string == ""){
        ui->labelError->setText("PIN ei voi olla tyhjä!");

        return false;
    }
    if(string.length() < 4){
        ui->labelError->setText("PIN pituus tulee olla neljä numeroa!");
        return false;
    }
    else{
        return true;
    }
}


void PINWindow::btnSignInSlot()
{

    // Tarkistetaan onko PIN format oikein
    if(!checkPINFormat(ui->linePIN->text())){
        //ui->labelError->setText("PIN ei voi olla tyhjä!");

        ui->linePIN->setFocus();

    }else{
        killTimer(timerId);
        ui->labelCount->setText(QString("Yhdistetään..."));
        this->setPin(ui->linePIN->text());


        QString url = Environment::base_url()+"login";
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QJsonObject jObject;

        jObject.insert("tunnistekoodi", this->getTunniste());
        jObject.insert("pin", this->getPin());

        QJsonDocument jsonDoc(jObject);
        reply = manager->post(request, jsonDoc.toJson());
        connect(reply, &QNetworkReply::finished, this, &PINWindow::loginAction);

 //       this->hide();
    }


}

void PINWindow::loginAction()
{


    QByteArray responseData=reply->readAll();
    if(responseData=="-4078" || responseData.length()==0){

              QMessageBox::information(
                this,
                tr("Yhteysvirhe"),
                tr("Virhe verkkoyhteydessä!"));

                this->close();
    }
    else {
        QJsonDocument jsonDoc=QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject=jsonDoc.object();


        if(jsonObject.contains("token")){
            QString token=jsonObject["token"].toString();
            QByteArray tokenBytes = token.toUtf8();

            int idtili = jsonObject["idtili"].toInt();

             QMessageBox::information(
                this,
                tr("Pankkiautomaatti"),
                tr("Tunnistautuminen onnistui!"));



            // TÄNNE SEURAAVA MENU
            MainMenu *mainMenu = new MainMenu(this);
            mainMenu->setIdtili(idtili);


             mainMenu->exec();


             this->hide();
        }
        else {

            ui->linePIN->clear();

            QMessageBox::information(
                this,
                tr("Pankkiautomaatti"),
                tr("Tunnus ja PIN eivät täsmää.") );

            this->close();
        }
    }

    reply->deleteLater();
}

void PINWindow::timerEvent(QTimerEvent *event)
{

    if(this->counter == 0){
        this->close();
    } else {
        this->counter -= 1;
        ui->labelCount->setText(QString("Palataan alkuvalikkoon %1 sekunnin kuluttua...").arg(this->counter));
    }

}
