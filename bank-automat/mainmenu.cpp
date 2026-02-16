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

void MainMenu::TapahtumatSlot()
{
    QByteArray response=reply->readAll();
    qDebug()<<"TapahtumatSlot()";
    qDebug()<<response;
    tilitapahtumatwindow *objtilitapahtumatwindow=new tilitapahtumatwindow(this);
    objtilitapahtumatwindow->setTilitapahtumatwindow(response);
    objtilitapahtumatwindow->show();


    reply->deleteLater();
}

void MainMenu::btnTapahtumatClicked()
{
    qDebug()<<"BtnTapahtumaClicked()";
    QString url=Environment::base_url()+"tilitapahtumat/"+ QString::number(idtili);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    qDebug()<<"Setheader";

    //WebTokenin alku
    qDebug()<<"WebTokenin alku";
    QString myToken="Bearer "+token;
    qDebug()<<"Ennen SetRawHeader";
    request.setRawHeader(QString("Authorization").toUtf8(),(myToken.toUtf8()));

    //WebTokenin loppu
    qDebug()<<"SetRawheaderin jälkeen";
    reply=manager->get(request);
    qDebug()<<"manager Request";

    connect(reply, &QNetworkReply::finished, this, &MainMenu::TapahtumatSlot);
    qDebug()<<"Slotti";

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
