#ifndef PINWINDOW_H
#define PINWINDOW_H

#include <QDialog>

#include "environment.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class PINWindow;
}

class PINWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PINWindow(QWidget *parent = nullptr);
    ~PINWindow();

    QString getTunniste() const;
    void setTunniste(const QString &newTunniste);

    QString getPin() const;
    void setPin(const QString &newPin);

private:
    Ui::PINWindow *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;

    int timerId;
    int counter = 10;
    QString tunniste;
    QString pin;

private slots:
    void btnSignInSlot();
    void loginAction();

protected:
    void timerEvent(QTimerEvent *event) override;

};

#endif // PINWINDOW_H
