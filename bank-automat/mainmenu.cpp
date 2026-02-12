#include "mainmenu.h"
#include "nostowindow.h"
#include "ui_mainmenu.h"


MainMenu::MainMenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    connect(ui->btnNosto, &QPushButton::clicked, this, &MainMenu::btnNostoSlot);
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

QString MainMenu::getToken() const
{
    return token;
}

void MainMenu::setToken(const QString &newToken)
{
    token = newToken;
}
