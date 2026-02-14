#ifndef ASIAKASTIEDOTWINDOW_H
#define ASIAKASTIEDOTWINDOW_H

#include <QDialog>

namespace Ui {
class asiakastiedotwindow;
}

class asiakastiedotwindow : public QDialog
{
    Q_OBJECT

public:
    explicit asiakastiedotwindow(QWidget *parent = nullptr);
    ~asiakastiedotwindow();

private:
    Ui::asiakastiedotwindow *ui;
};

#endif // ASIAKASTIEDOTWINDOW_H
