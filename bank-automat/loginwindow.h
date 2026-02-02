#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>


#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();


private slots:
    void btnContinueSlot();

private:
    Ui::LoginWindow *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
};

#endif // LOGINWINDOW_H
