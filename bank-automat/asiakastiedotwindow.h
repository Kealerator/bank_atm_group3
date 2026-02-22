#ifndef ASIAKASTIEDOTWINDOW_H
#define ASIAKASTIEDOTWINDOW_H

#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>


namespace Ui {
class asiakastiedotwindow;
}

class asiakastiedotwindow : public QDialog
{
    Q_OBJECT

public:
    explicit asiakastiedotwindow(QWidget *parent = nullptr);
    ~asiakastiedotwindow();

    void setIdTili(int newIdTili);
    void requestAsiakastiedot();

    void setToken(const QString &newToken);

private:
    Ui::asiakastiedotwindow *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    int idTili;
    QString token;
    QTimer *inactivityTimer;

private slots:
    void btnReturnSlot();
    void asiakastiedotSlot();
    void timeout();
    void resetTimer();
};

#endif // ASIAKASTIEDOTWINDOW_H
