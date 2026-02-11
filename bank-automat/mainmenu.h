#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>

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

private:
    Ui::MainMenu *ui;


    int idtili;
};

#endif // MAINMENU_H
