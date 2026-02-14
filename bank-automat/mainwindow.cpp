#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "loginwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnStart, &QPushButton::clicked, this, &MainWindow::btnStartSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnStartSlot()
{
    this->hide();
    LoginWindow *login = new LoginWindow(this);
    login->exec();
    this->show();
}
