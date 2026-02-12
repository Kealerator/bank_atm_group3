#ifndef TILITAPAHTUMATWINDOW_H
#define TILITAPAHTUMATWINDOW_H

#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
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

private:
    Ui::tilitapahtumatwindow *ui;
    QByteArray Tilitapahtumatwindow;
};

#endif // TILITAPAHTUMATWINDOW_H
