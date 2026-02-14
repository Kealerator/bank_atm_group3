#include "asiakastiedotwindow.h"
#include "ui_asiakastiedotwindow.h"

asiakastiedotwindow::asiakastiedotwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::asiakastiedotwindow)
{
    ui->setupUi(this);
}

asiakastiedotwindow::~asiakastiedotwindow()
{
    delete ui;
}
