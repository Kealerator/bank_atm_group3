#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>

#include "environment.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
namespace Ui {
class MainMenu;
}

class MainMenu : public QDialog
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();


    int getIdtili() const;
    void setIdtili(int newIdtili);
    QString getToken() const;
    void setToken(const QString &newToken);

private slots:
    void btnNostoSlot();
    void btnTapahtumatSlot();
    void btnSaldoSlot();
    void btnAsiakastiedotSlot();
    void btnLogoutSlot();

    void aikakatkaisu();
    void nollaaAjastin();

private:
    Ui::MainMenu *ui;
    QString token;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QTimer *inaktiivisuusAjastin;

    int idtili;
};

#endif // MAINMENU_H
