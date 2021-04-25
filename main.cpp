#include "mainwindow.h"
#include <QApplication>
#include "Move.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Move::Instance()->start();
    MainWindow w;
    w.setProperty("CanMove",false);
    w.show();
    return a.exec();
}
