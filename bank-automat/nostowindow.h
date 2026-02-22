#ifndef NOSTOWINDOW_H
#define NOSTOWINDOW_H

#include <QDialog>
#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>


namespace Ui {
class NostoWindow;
}

class NostoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NostoWindow(QWidget *parent = nullptr);
    ~NostoWindow();
    void setToken(const QString &newToken);
    void setIdtili(int newIdtili);
    int getIdtili() const;

private slots:
    void btnTakaisinSlot();
    void vastaus(QNetworkReply *reply);
    void nosta20();
    void nosta40();
    void nosta50();
    void nosta80();
    void nosta100();
    void nosta200();
    void nostaMuuSumma();
    void aikakatkaisu();
    void nollaaAjastin();

private:
    Ui::NostoWindow *ui;
    int idtili;
    QString token;
    QNetworkAccessManager *manager;
    void lahetaNostoPyynto(int summa);
    QTimer *inaktiivisuusAjastin;
    void closeEvent(QCloseEvent *event);
};

#endif // NOSTOWINDOW_H
