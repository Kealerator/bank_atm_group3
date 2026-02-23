#ifndef TILITAPAHTUMATWINDOW_H
#define TILITAPAHTUMATWINDOW_H

#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "tilitapahtumat.h"
#include <QTimer>

namespace Ui {
class tilitapahtumatwindow;
}

class tilitapahtumatwindow : public QDialog
{
    Q_OBJECT

public:
    explicit tilitapahtumatwindow(QWidget *parent = nullptr);
    ~tilitapahtumatwindow();

    void setToken(const QString &newToken);
    void setIdtili(int newIdtili);
    void btnTapahtumatClicked();
    void Tilitapahtumatslot();
    void PäivitäTapahtumat(const QVector<tilitapahtumat>& kaikkiTilitapahtumat);

private slots:
    void btnPoistuslot();
    void btnVasenSlot();
    void btnOikeaSlot();
    void aikakatkaisu();
    void nollaaAjastin();




private:
    Ui::tilitapahtumatwindow *ui;
    int idtili;
    QString token;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QTimer *inaktiivisuusAjastin;
    QVector<tilitapahtumat> kaikkiTilitapahtumat;
    QVector<tilitapahtumat> listTilitapahtumat;
    int nykyinenIndeksi;
    void closeEvent(QCloseEvent *event);
};

#endif // TILITAPAHTUMATWINDOW_H
