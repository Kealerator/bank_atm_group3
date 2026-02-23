#include "asiakastiedotwindow.h"
#include "ui_asiakastiedotwindow.h"
#include "environment.h"

asiakastiedotwindow::asiakastiedotwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::asiakastiedotwindow)
{
    ui->setupUi(this);

    //Luodaan QNetworkAccessManager olio verkkopyyntöjä varten.
    manager = new QNetworkAccessManager(this);

    //10s aikakatkaisun alustus.
    inactivityTimer = new QTimer(this);
    inactivityTimer->setInterval(30000);

    //Yhdistetään signaalit luokan slot funktioihin.
    connect(inactivityTimer, &QTimer::timeout, this, &asiakastiedotwindow::timeout);
    connect(ui->btnReturn, &QPushButton::clicked, this, &::asiakastiedotwindow::btnReturnSlot);
}

asiakastiedotwindow::~asiakastiedotwindow()
{
    delete ui;
}

//Setteri joka asettaa kirjautumisessa saadun idTili tunnisteen.
void asiakastiedotwindow::setIdTili(int newIdTili)
{
    idTili = newIdTili;
}

//Setteri joka asettaa kirjautumisessa saadun tokenin.
void asiakastiedotwindow::setToken(const QString &newToken)
{
    token = newToken;
}


//HTTP GET pyyntö joka hakee palvelimelta kirjautuneen asiakastiedot.
void asiakastiedotwindow::requestAsiakastiedot()
{
    //Käynnistää ajastimen.
    resetTimer();

    //Muodostaa URLin jossa kirjautuneen idTili numero ja luo HTTP GET pyynnön.
    QString base_url =Environment::base_url()+"asiakas/tiedot/" + QString::number(idTili);
    QNetworkRequest request(base_url);

    //Kertoo ContentTypeHeader:ille että pyyntö on JSON muotoista ja asettaa Authorization tokenin.
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer " + token.toUtf8());

    //Lähettää pyynnön ja yhdistää vastauksen slot funktioon.
    reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &asiakastiedotwindow::asiakastiedotSlot);
}

//Käynnistää/nollaa ajastimen.
void asiakastiedotwindow::resetTimer()
{
    inactivityTimer->start();
}

//Luetaan pyydetty vastaus ja näytetään se UI:ssa.
void asiakastiedotwindow::asiakastiedotSlot()
{
    //Lukee palvelimen JSON vastauksen ja päivittää tiedot käyttöliittymän asiakkaan tiedoilla.
    QByteArray response = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
    QJsonArray jsonArray = jsonDoc.array();
    QJsonObject jsonObject = jsonArray.at(0).toObject();

    //Muuntaa palvelimen JSON vastauksen ja täyttää UI:n label kentät asiakkaan tiedoilla.
    ui->labelFname->setText(jsonObject["etunimi"].toString());
    ui->labelLname->setText(jsonObject["sukunimi"].toString());
    ui->labelAddress->setText(jsonObject["osoite"].toString());
    ui->labelPnumber->setText(jsonObject["puhelinnumero"].toString());

    //Vapauttaa olion muistin.
    reply->deleteLater();
}

//Takaisin nappi jolla päästään takaisin päävalikkoon
void asiakastiedotwindow::btnReturnSlot()
{
    //Pysäyttää ajastimen ja sulkee ikkunan.
    inactivityTimer->stop();
    this->close();
}

//10s jälkeen paluu päävalikkoon.
void asiakastiedotwindow::timeout()
{
    //Pysäyttää ajastimen ja piilottaa ikkunan
    inactivityTimer->stop();;
    this->hide();

    //siirtyy takaisin parent ikkunaan.
    QWidget *parent = parentWidget();
    if (parent)
        parent->show();
}

void asiakastiedotwindow::closeEvent(QCloseEvent *event) {
    inactivityTimer->stop();
    QDialog::closeEvent(event);
}
