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
    ui->linePIN->setFocus();

}

PINWindow::~PINWindow()
{
    killTimer(timerId);
    delete ui;
}

void PINWindow::btnSignInSlot()
{
    if(ui->linePIN->text() == ""){
        ui->labelError->setText("PIN ei voi olla tyhjä!");
        ui->linePIN->setFocus();
    }else{
        this->hide();
    }
}

void PINWindow::timerEvent(QTimerEvent *event)
{

    if(this->counter == 0){
        this->close();
    } else {
        this->counter -= 1;
        ui->labelCount->setText(QString("Palataan alkuvalikkoon %1 sekunnin kuluttua...").arg(this->counter));
    }

}
