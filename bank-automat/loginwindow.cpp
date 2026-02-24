#include "loginwindow.h"
#include "pinwindow.h"

#include "QDebug"
#include "ui_loginwindow.h"



LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    connect(ui->btnContinue, &QPushButton::clicked, this, &LoginWindow::btnContinueSlot);


}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::btnContinueSlot()
{

    // Mikäli käyttäjä yrittää kirjautua sisään tyhjällä tunnistekoodilla
    // ilmoitetaan siitä käyttäjälle
    if(ui->lineTunnistekoodi->text() == ""){
        ui->labelErrorMsg->setText("Tunnistekoodi ei voi olla tyhjä!");
    }else{
        // Muussa tapauksessa resetoidaan varoituskenttä
        ui->labelErrorMsg->setText("");

        // Luodaan PIN syöttöikkuna ja asetetaan sen sisällä olevaan private
        // muuttujaan tunnuskoodi talteen

        PINWindow *pinQuery = new PINWindow(this);
        pinQuery->setTunniste(ui->lineTunnistekoodi->text());

        this->hide();
        pinQuery->exec();

    }


}
