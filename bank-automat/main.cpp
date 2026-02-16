#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QFile file(":/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)){
        QString stylesheet = file.readAll();
        a.setStyleSheet(stylesheet);

        qDebug() << "style.qss avaaminen onnistui!";
    }else {
        qDebug() << "style.qss avaaminen epäonnistui!";
    }

    MainWindow w;
    w.show();
    return a.exec();
}
