#ifndef TILITAPAHTUMATWINDOW_H
#define TILITAPAHTUMATWINDOW_H

#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include "tilitapahtumat.h"

namespace Ui {
class tilitapahtumatwindow;
}

class tilitapahtumatwindow : public QDialog
{
    Q_OBJECT

public:
    explicit tilitapahtumatwindow(QWidget *parent = nullptr);
    ~tilitapahtumatwindow();

    void setTilitapahtumatwindow(const QByteArray &newtilitapahtumatwindow);

private slots:
    void btnPoistuslot();

private:
    Ui::tilitapahtumatwindow *ui;
    int idtili;
    QString token;
    QNetworkAccessManager *manager;
    QByteArray Tilitapahtumatwindow;
};

#endif // TILITAPAHTUMATWINDOW_H
