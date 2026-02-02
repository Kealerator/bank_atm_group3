#ifndef PINWINDOW_H
#define PINWINDOW_H

#include <QDialog>

namespace Ui {
class PINWindow;
}

class PINWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PINWindow(QWidget *parent = nullptr);
    ~PINWindow();

private:
    Ui::PINWindow *ui;
    int timerId;
    int counter = 10;

private slots:
    void btnSignInSlot();

protected:
    void timerEvent(QTimerEvent *event) override;

};

#endif // PINWINDOW_H
