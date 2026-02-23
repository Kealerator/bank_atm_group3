#include "nostowindow.h"
#include "ui_nostowindow.h"
#include "environment.h"

NostoWindow::NostoWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NostoWindow)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);

    // Inaktiivisuus ajastimen luominen
    inaktiivisuusAjastin = new QTimer(this);
    inaktiivisuusAjastin->setInterval(30000);
    connect(inaktiivisuusAjastin, &QTimer::timeout, this, &NostoWindow::aikakatkaisu);
    inaktiivisuusAjastin->start();

    connect(manager, &QNetworkAccessManager::finished, this, &NostoWindow::vastaus);
    connect(ui->btnReturn, &QPushButton::clicked, this, &NostoWindow::btnTakaisinSlot);

    // Nostosummat
    connect (ui->btn20, &QPushButton::clicked, this, &NostoWindow::nosta20);
    connect (ui->btn40, &QPushButton::clicked, this, &NostoWindow::nosta40);
    connect (ui->btn50, &QPushButton::clicked, this, &NostoWindow::nosta50);
    connect (ui->btn80, &QPushButton::clicked, this, &NostoWindow::nosta80);
    connect (ui->btn100, &QPushButton::clicked, this, &NostoWindow::nosta100);
    connect (ui->btn200, &QPushButton::clicked, this, &NostoWindow::nosta200);
    connect(ui->btnNostaMuu, &QPushButton::clicked, this, &NostoWindow::nostaMuuSumma);

    // Inaktiivisuus ajastimen nollaus nappien painalluksista
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

// Sulkee nostoikkunan napista
void NostoWindow::btnTakaisinSlot()
{
    this->hide();
}

// Palvelimen vastauksen käsittely
void NostoWindow::vastaus(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    QJsonObject obj = QJsonDocument::fromJson(data).object();

    // Verkkovirheiden tarkistus
    if (reply->error() != QNetworkReply::NoError) {
        ui->labelStatus->setText("Verkkovirhe");
        reply->deleteLater();
        return;
    }

    // Jos palvelin palauttaa virheen
    if (obj.contains("success") && !obj["success"].toBool()) {

        QString viesti = obj["message"].toString();
        QString teksti = "Virhe: " + viesti;

        // Saldon lisäis, jos palvelin palauttaa sen
        if (obj.contains("saldo")) {
            double saldo = obj["saldo"].toDouble();
            teksti += "\nSaldo: " + QString::number(saldo);
        }

        // Käytettävissä olevan summan lisäys
        if (obj.contains("käytettävissä")) {
            double kaytettavissa = obj["käytettävissä"].toDouble();
            teksti += "\nKäytettävissä: " + QString::number(kaytettavissa);
        }

        ui->labelStatus->setText(teksti);
        reply->deleteLater();
        return;
    }

    // Onnistunut nosto
    QString viesti = obj["message"].toString();
    QString teksti = viesti;

    // Uusi saldo
    if (obj.contains("uusiSaldo")) {
        double saldo = obj["uusiSaldo"].toDouble();
        teksti += "\nSaldo: " + QString::number(saldo);
    }
    // Käytettävissä oleva summa
    if (obj.contains("käytettävissä")) {
        double kaytettavissa = obj["käytettävissä"].toDouble();
        teksti += "\nKäytettävissä: " + QString::number(kaytettavissa);
    }

    ui->labelStatus->setText(teksti);
    reply->deleteLater();
}

// Kiinteät nostosummat napeille
void NostoWindow::nosta20()
{
    inaktiivisuusAjastin->stop();
    lahetaNostoPyynto(20);
    inaktiivisuusAjastin->start();
}

void NostoWindow::nosta40()
{
    inaktiivisuusAjastin->stop();
    lahetaNostoPyynto(40);
    inaktiivisuusAjastin->start();
}

void NostoWindow::nosta50()
{
    inaktiivisuusAjastin->stop();
    lahetaNostoPyynto(50);
    inaktiivisuusAjastin->start();
}

void NostoWindow::nosta80()
{
    inaktiivisuusAjastin->stop();
    lahetaNostoPyynto(80);
    inaktiivisuusAjastin->start();
}

void NostoWindow::nosta100()
{
    inaktiivisuusAjastin->stop();
    lahetaNostoPyynto(100);
    inaktiivisuusAjastin->start();
}

void NostoWindow::nosta200()
{
    inaktiivisuusAjastin->stop();
    lahetaNostoPyynto(200);
    inaktiivisuusAjastin->start();
}

// Vapaavalintaisen summan nosto
void NostoWindow::nostaMuuSumma()
{
    inaktiivisuusAjastin->stop();
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
    inaktiivisuusAjastin->start();
}

// Aikakatkaisun suoritus
void NostoWindow::aikakatkaisu()
{
    inaktiivisuusAjastin->stop();

    this->close();

}

// Ajastaminen nollaus
void NostoWindow::nollaaAjastin()
{
    inaktiivisuusAjastin->start();
}


//
int NostoWindow::getIdtili() const
{
    return idtili;
}

void NostoWindow::setIdtili(int newIdtili)
{
    idtili = newIdtili;
}

// Nosto tapahtuman POST pyyntö
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

void NostoWindow::closeEvent(QCloseEvent *event) {
    inaktiivisuusAjastin->stop();
    QDialog::closeEvent(event);
}
