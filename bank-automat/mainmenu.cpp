#include "mainmenu.h"
#include "nostowindow.h"
#include "ui_mainmenu.h"
#include "tilitapahtumatwindow.h"
#include "tilitapahtumat.h"
#include "saldowindow.h"
#include "asiakastiedotwindow.h"


MainMenu::MainMenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    connect(ui->btnNosto, &QPushButton::clicked, this, &MainMenu::btnNostoSlot);
    connect(ui->btnTapahtumat, &QPushButton::clicked, this, &MainMenu::btnTapahtumatSlot);
    connect(ui->btnSaldo, &QPushButton::clicked, this, &MainMenu::btnSaldoSlot);
    connect(ui->btnTiedot, &QPushButton::clicked, this, &MainMenu::btnAsiakastiedotSlot);

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
    this->hide();
    NostoWindow *nosto = new NostoWindow(this);
    nosto->setIdtili(idtili);
    nosto->setToken(token);
    nosto->exec();
    this->show();
}

void MainMenu::btnTapahtumatSlot()
{ 
    this->hide();
    tilitapahtumatwindow *tapahtumat = new tilitapahtumatwindow(this);
    tapahtumat->setIdtili(idtili);
    tapahtumat->setToken(token);
    tapahtumat->btnTapahtumatClicked();
    tapahtumat->exec();
    this->show();

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
    this->hide();
    saldowindow *objSaldo = new saldowindow(this);
    objSaldo->setIdTili(idtili);
    objSaldo->setToken(token);
    objSaldo->requestSaldo();
    objSaldo->exec();
    this->show();

}

void MainMenu::btnAsiakastiedotSlot(){
    this->hide();
    asiakastiedotwindow *objAsiakastiedot = new asiakastiedotwindow(this);
    objAsiakastiedot->setIdTili(idtili);
    objAsiakastiedot->setToken(token);
    objAsiakastiedot->requestAsiakastiedot();
    objAsiakastiedot->exec();
    this->show();

}
