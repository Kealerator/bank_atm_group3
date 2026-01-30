#include "pinwindow.h"
#include "ui_pinwindow.h"
#include "QDebug"

PINWindow::PINWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PINWindow)
{
    ui->setupUi(this);
    connect(ui->btnSignIn, &QPushButton::clicked, this, &PINWindow::btnSignInSlot);


    timerId = startTimer(1000);
}

PINWindow::~PINWindow()
{
    killTimer(timerId);
    delete ui;
}

void PINWindow::btnSignInSlot()
{
    if(ui->linePIN->text() == ""){
        qDebug() << "PIN tyhjä!";
    }else{
        this->hide();
    }
}

void PINWindow::timerEvent(QTimerEvent *event)
{
    if(this->counter == 0){
        qDebug() << "Aika loppui!";
        this->close();
    } else {
        this->counter -= 1;
        qDebug() << this->counter;
    }

}
