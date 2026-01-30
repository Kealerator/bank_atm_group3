#include "loginwindow.h"
#include "pinwindow.h"
#include "QDebug"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    connect(ui->btnToPIN, &QPushButton::clicked, this, &LoginWindow::btnPINSlot);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::btnPINSlot()
{

    if(ui->lineTunnistekoodi->text() == ""){
        qDebug() << "Tunnistekoodi tyhjä!";
    }else{
        this->hide();
        PINWindow pinQuery;
        pinQuery.exec();
    }


}
