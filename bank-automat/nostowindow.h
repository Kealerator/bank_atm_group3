#ifndef NOSTOWINDOW_H
#define NOSTOWINDOW_H

#include <QDialog>

namespace Ui {
class NostoWindow;
}

class NostoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NostoWindow(QWidget *parent = nullptr);
    ~NostoWindow();

private:
    Ui::NostoWindow *ui;
};

#endif // NOSTOWINDOW_H
