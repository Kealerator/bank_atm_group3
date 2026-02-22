#include "mainmenu.h"
#include "nostowindow.h"
#include "ui_mainmenu.h"
#include "tilitapahtumatwindow.h"
#include "saldowindow.h"
#include "asiakastiedotwindow.h"

#include <QMessageBox>


MainMenu::MainMenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    inaktiivisuusAjastin = new QTimer(this);
    inaktiivisuusAjastin->setInterval(10000);
    connect(inaktiivisuusAjastin, &QTimer::timeout, this, &MainMenu::aikakatkaisu);
    inaktiivisuusAjastin->start();

    connect(ui->btnNosto, &QPushButton::clicked, this, &MainMenu::btnNostoSlot);
    connect(ui->btnTapahtumat, &QPushButton::clicked, this, &MainMenu::btnTapahtumatSlot);
    connect(ui->btnSaldo, &QPushButton::clicked, this, &MainMenu::btnSaldoSlot);
    connect(ui->btnTiedot, &QPushButton::clicked, this, &MainMenu::btnAsiakastiedotSlot);
    connect(ui->btnLogout, &QPushButton::clicked, this, &MainMenu::btnLogoutSlot);

}

MainMenu::~MainMenu()
{
    delete ui;
}

int MainMenu::getIdtili() const
{
    return idtili;
}

void MainMenu::setIdtili(int newIdtili)
{
    idtili = newIdtili;
    ui->labelidTili->setText("Tili-ID: " + QString::number(idtili));
}

void MainMenu::btnNostoSlot()
{

    inaktiivisuusAjastin->stop();
    NostoWindow *nosto = new NostoWindow(this);
    nosto->setIdtili(idtili);
    nosto->setToken(token);
    nosto->exec();
    this->show();
    inaktiivisuusAjastin->start();
}

void MainMenu::btnTapahtumatSlot()
{
    inaktiivisuusAjastin->stop();
    this->hide();
    tilitapahtumatwindow *tapahtumat = new tilitapahtumatwindow(this);
    tapahtumat->setIdtili(idtili);
    tapahtumat->setToken(token);
    tapahtumat->btnTapahtumatClicked();
    tapahtumat->exec();
    this->show();
    inaktiivisuusAjastin->start();

}

QString MainMenu::getToken() const
{
    return token;
}

void MainMenu::setToken(const QString &newToken)
{
    token = newToken;
}

void MainMenu::btnSaldoSlot(){

    inaktiivisuusAjastin->stop();
    saldowindow *objSaldo = new saldowindow(this);
    objSaldo->setIdTili(idtili);
    objSaldo->setToken(token);
    objSaldo->requestSaldo();
    objSaldo->exec();
    this->show();
    inaktiivisuusAjastin->start();

}

void MainMenu::btnAsiakastiedotSlot(){
    inaktiivisuusAjastin->stop();
    asiakastiedotwindow *objAsiakastiedot = new asiakastiedotwindow(this);
    objAsiakastiedot->setIdTili(idtili);
    objAsiakastiedot->setToken(token);
    objAsiakastiedot->requestAsiakastiedot();
    objAsiakastiedot->exec();
    this->show();
    inaktiivisuusAjastin->start();

}

void MainMenu::btnLogoutSlot()
{
    // Asetetaan tokenin ja idTilin arvot kelvottomiksi
    inaktiivisuusAjastin->stop();
    this->setIdtili(-1);
    this->setToken(NULL);
    this->close();
}

void MainMenu::aikakatkaisu()
{
    inaktiivisuusAjastin->stop();

    this->btnLogoutSlot();

    QMessageBox *msgDialog = new QMessageBox(this);
    msgDialog->setStandardButtons(QMessageBox::Ok);
    msgDialog->setIcon(QMessageBox::Information);

    msgDialog->setWindowTitle("Aikakatkaisu");
    msgDialog->setText("Yhteys verkkopalvelimeen katkaistiin inaktiivisuuden vuoksi!");
    msgDialog->show();
}

void MainMenu::nollaaAjastin()
{
    inaktiivisuusAjastin->start();
}
