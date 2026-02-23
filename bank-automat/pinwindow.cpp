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

    // Käytetään QTimer moduulia päivittämään QLabel olioon montako sekuntia
    // käyttäjällä on aikaa syötätä PIN (1000ms välein = 1s)
    timerId = startTimer(1000);
    ui->linePIN->setFocus();

}

PINWindow::~PINWindow()
{
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

// Erillinen funktio PIN koodin tarkistamiselle, voi muuttaa esim
// ettei voi syöttää lainkaan kirjaimia
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

        ui->linePIN->setFocus();

    }else{
        // Mikäli PIN on oikeaa formaattia niin pysäytetään ajastin
        // ja indikoidaan käyttäjälle heti että yhdistetään palvelimeen
        killTimer(timerId);
        ui->labelCount->setText(QString("Yhdistetään..."));

        // Asetetaan lineEdit olioon syötetty teksti private muuttujaan
        // joka liitetään sitten erilliseen HTTP pyyntöön
        this->setPin(ui->linePIN->text());


        QString url = Environment::base_url()+"login";
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QJsonObject jObject;

        // Asetetaan tunnistekoodi ja pin muuttujista HTTP pyyntöön
        // aktivoidaan loginAction jossa sitten reagoidaan HTTP pyynnön vastaukseen
        jObject.insert("tunnistekoodi", this->getTunniste());
        jObject.insert("pin", this->getPin());

        QJsonDocument jsonDoc(jObject);
        reply = manager->post(request, jsonDoc.toJson());
        connect(reply, &QNetworkReply::finished, this, &PINWindow::loginAction);
    }


}

void PINWindow::loginAction()
{
    // Luodaan virheikkuna mahdollisia virheitä varten

    QMessageBox *msgDialog = new QMessageBox(this);
    msgDialog->setStandardButtons(QMessageBox::Ok);
    msgDialog->setIcon(QMessageBox::Information);


    QByteArray responseData=reply->readAll();


    // Mikäli palvelimeen ei saada yhteyttä niin ilmoitetaan siitä aiemmin alustetussa
    // virheikkunassa ja tuodaan se esiin

    if(responseData=="-4078" || responseData.length()==0){
        msgDialog->setWindowTitle("Yhteysvirhe");
        msgDialog->setText("Virhe verkkoyhteydessä!");
        msgDialog->show();

        this->close();
    }
    else {
        // Mikäli palvelimeen saadaan yhteys, tarkistetaan saadaanko HTTP
        // pyyntöön vastaukseksi token joka indikoi että sisäänkirjautuminen on onnistunut

        QJsonDocument jsonDoc=QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject=jsonDoc.object();


        if(jsonObject.contains("token")){
            QString token=jsonObject["token"].toString();
            QByteArray tokenBytes = token.toUtf8();

            // Mikäli token löytyy niin tallennetaan HTTP vastauksesta myös
            // tilin id -tunnus johon kortti (tunnistekoodi) on liitetty.

            int idtili = jsonObject["idtili"].toInt();


            // Alustetaan pääkäyttöliittymä ja tallennetaan tilin id ja token
            // sen private muuttujiin.
            MainMenu *mainMenu = new MainMenu(this);
            mainMenu->setIdtili(idtili);
            mainMenu->setToken(token);


            this->hide();
            mainMenu->exec();

        }
        else {

            // Mikäli HTTP pyyntö ei saa vastaukseksi tokenia niin QLineEdit olion sisältö tyhjennetään
            // ja annetaan virheikkunalla virheilmoitus jonka sisältö löytyy HTTP pyynnön vastauksesta.

            ui->linePIN->clear();

            QJsonDocument json_doc = QJsonDocument::fromJson(responseData);
            QJsonObject jsonObj = json_doc.object();
            QString msg = jsonObj["message"].toString();


            // Asetetaan virheikkunan otsikko ja sisältö
            msgDialog->setWindowTitle("Virhe kirjautumisessa");
            msgDialog->setText(msg);
            msgDialog->show();

            this->close();
        }
    }

    reply->deleteLater();
}

void PINWindow::timerEvent(QTimerEvent *event)
{
    // PIN -olion private muuttujaa counter vähennetään 1000ms välein

    //Mikäli sen arvo on 0, pysäytetään QTimer ajastin ja suljetaan ikkuna, jolloin päädytään aloituskäyttöliitymään
    if(this->counter == 0){
        killTimer(timerId);
        this->close();
    } else {
        this->counter -= 1;

        // Indikoidaan käyttäjälle QLabel -olion tekstillä kuinka monta sekuntia hänellä on vielä aikaa syöttää PIN.
        ui->labelCount->setText(QString("Palataan alkuvalikkoon %1 sekunnin kuluttua...").arg(this->counter));
    }

}
