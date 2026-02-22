#include "saldowindow.h"
#include "ui_saldowindow.h"
#include "environment.h"

saldowindow::saldowindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::saldowindow)
{
    ui->setupUi(this);

    //Luodaan QNetworkAccessManager olio verkkopyyntöjä varten.
    manager = new QNetworkAccessManager(this);

    //10s aikakatkaisun alustus.
    inactivityTimer = new QTimer(this);
    inactivityTimer->setInterval(10000);

    //Yhdistetään signaalit luokan slot funktioihin.
    connect(inactivityTimer, &QTimer::timeout, this, &saldowindow::timeout);
    connect(ui->btnReturn, &QPushButton::clicked, this, &::saldowindow::btnReturnSlot);
}

saldowindow::~saldowindow()
{
    delete ui;
}

//Setteri joka asettaa kirjautumisessa saadun idTili tunnisteen.
void saldowindow::setIdTili(int newIdTili)
{
    idTili = newIdTili;
}

//Setteri joka asettaa kirjautumisessa saadun tokenin.
void saldowindow::setToken(const QString &newToken)
{
    token = newToken;
}

//HTTP GET pyyntö joka hakee palvelimelta kirjautuneen tilin saldon.
void saldowindow::requestSaldo(){

    //Käynnistää 10s ajastimen
    resetTimer();


    //Muodostaa URLin jossa kirjautuneen idTili numero ja luo HTTP GET pyynnön.
    QString base_url =Environment::base_url()+"tili/saldo/" + QString::number(idTili);
    QNetworkRequest request(base_url);

    //Kertoo ContentTypeHeader:ille että pyyntö on JSON muotoista ja asettaa Authorization tokenin.
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer " + token.toUtf8());

    reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &saldowindow::saldoSlot);
}

//Käynnistää/nollaa ajastimen.
void saldowindow::resetTimer()
{
    inactivityTimer->start();
}

//Luetaan pyydetty vastaus ja näytetään se UI:ssa.
void saldowindow::saldoSlot()
{
    //Lukee palvelimen JSON vastauksen ja päivittää saldon käyttöliittymään asiakkaan tiedoilla.
    QByteArray response = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
    QJsonArray jsonArray = jsonDoc.array();
    QJsonObject jsonObject = jsonArray.at(0).toObject();

    // Muuntaa palvelimen JSON vastauksen ja täyttää UI:n label kentät asiakkaan tiedoilla ja saldolla.
    ui->labelFname->setText(jsonObject["etunimi"].toString());
    ui->labelLname->setText(jsonObject["sukunimi"].toString());
    ui->labelSaldo->setText(QString::number(jsonObject["saldo"].toString().toDouble(),'f', 2));

    //Vapauttaa olion muistin.
    reply->deleteLater();
}

//Takaisin nappi jolla päästään takaisin päävalikkoon
void saldowindow::btnReturnSlot()
{
    //Pysäyttää ajastimen ja sulkee ikkunan.
    inactivityTimer->stop();
    this->hide();
}

//10s jälkeen paluu päävalikkoon.
void saldowindow::timeout()
{
    //Pysäyttää ajastimen ja piilottaa ikkunan
    inactivityTimer->stop();
    this->hide();

    //siirtyy takaisin parent ikkunaan.
    QWidget *parent = parentWidget();
    if (parent)
        parent->show();
}
