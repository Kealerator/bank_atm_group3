#ifndef SALDOWINDOW_H
#define SALDOWINDOW_H

#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

namespace Ui {
class saldowindow;
}

class saldowindow : public QDialog
{
    Q_OBJECT

public:
    explicit saldowindow(QWidget *parent = nullptr);
    ~saldowindow();

    void setIdTili(int newIdTili);

    void setToken(const QString &newToken);
    void requestSaldo();


private:
    Ui::saldowindow *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    int idTili;
    QString token;



private slots:
    void btnReturnSlot();
    void saldoSlot();
};

#endif // SALDOWINDOW_H
