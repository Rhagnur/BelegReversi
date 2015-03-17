//#include "mainwindow.h"
//#include <QApplication>
#include "controllerField.h"

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    //return a.exec();
    controllerField* reversiField;
    reversiField = new controllerField(6);
    reversiField->startGame();
}
