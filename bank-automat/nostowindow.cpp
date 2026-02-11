#include "nostowindow.h"
#include "ui_nostowindow.h"

NostoWindow::NostoWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NostoWindow)
{
    ui->setupUi(this);
}

NostoWindow::~NostoWindow()
{
    delete ui;
}
