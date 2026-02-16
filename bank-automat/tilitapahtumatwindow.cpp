#include "tilitapahtumatwindow.h"
#include "ui_tilitapahtumatwindow.h"
#include "environment.h"
#include <QStandardItemModel>

tilitapahtumatwindow::tilitapahtumatwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::tilitapahtumatwindow)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(ui->btnReturn, &QPushButton::clicked, this, &tilitapahtumatwindow::btnPoistuslot);
}

tilitapahtumatwindow::~tilitapahtumatwindow()
{
    delete ui;
}
void tilitapahtumatwindow::setTilitapahtumatwindow(const QByteArray &newtilitapahtumatwindow)
{
    Tilitapahtumatwindow = newtilitapahtumatwindow;
    qDebug()<<"Tilitapahtumat form";
    //qDebug()<<tilitapahtumatwindow;

    QJsonDocument json_doc = QJsonDocument::fromJson(Tilitapahtumatwindow);
    QJsonArray json_array=json_doc.array();

    QVector<tilitapahtumat> listTilitapahtumat;
    for (const QJsonValue &value : json_array) {
        if (value.isObject()) {
            tilitapahtumat tilitapahtuma = tilitapahtumat::mapJson(value.toObject());
            listTilitapahtumat.append(tilitapahtuma);
        }
    }

    auto *tableModel = new QStandardItemModel(listTilitapahtumat.size(), 4, this);
    tableModel->setHorizontalHeaderLabels({ tr("idtili"), tr("tilinumero"), tr("tapahtumat"), tr("summa"), tr("ajankohta") });
    for (int row = 0; row<listTilitapahtumat.size(); ++row){
        const tilitapahtumat &tilitapahtuma = listTilitapahtumat[row];
        tableModel->setItem(row, 0, new QStandardItem(QString::number(tilitapahtuma.idtili)));
        tableModel->setItem(row, 1, new QStandardItem(tilitapahtuma.tilinumero));
        tableModel->setItem(row, 2, new QStandardItem(tilitapahtuma.tapahtumat));
        tableModel->setItem(row, 3, new QStandardItem(QString::number(tilitapahtuma.summa)));
        tableModel->setItem(row, 4, new QStandardItem(tilitapahtuma.ajankohta));
    }
    ui->tilitapahtumatTable->setModel(tableModel);
    ui->tilitapahtumatTable->verticalHeader()->setVisible(false);
    ui->tilitapahtumatTable->resizeColumnsToContents();
}

void tilitapahtumatwindow::btnPoistuslot()
{
    this->parentWidget()->show();
    this->close();
}
