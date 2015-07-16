#include "mainwindow.h"
#include <iostream>
#include <string>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mainUI(new Ui::MainWindow), gameUI(new Ui::GameWindow)
{
    mainUI->setupUi(this);

    controllField = new controllerField();
    myMenu = new menu();

    //ui->graphicsViewField->fitInView(controllField->passViewField()->sceneRect());

}

MainWindow::~MainWindow()
{
    delete mainUI;
}

void MainWindow::on_pushButton_clicked()
{
    mainUI->graphicsViewField->setScene(controllField->passViewField());
    controllField->initControllerField(4, mainUI->graphicsViewField->width(), mainUI->graphicsViewField->height());
    mainUI->label->setText(QString::fromStdString(controllField->getInfoText()));
    mainUI->labelPlayer1->setText(QString::fromStdString(controllField->getPlayer1Text()));
    mainUI->labelPlayer2->setText(QString::fromStdString(controllField->getPlayer2Text()));
    std::cout << "Text 1 " + controllField->getPlayer1Text() << std::endl;
    std::cout << "Text 2 " + controllField->getPlayer2Text() << std::endl;
    std::cout << "SetFieldSize to " + std::to_string(mainUI->graphicsViewField->width()) + " x " + std::to_string(mainUI->graphicsViewField->height()) << std::endl;
    mainUI->graphicsViewField->viewport()->installEventFilter(this);

}

void MainWindow::on_pushButton_2_clicked()
{

    if(controllField->isInit && !controllField->searchPossibleTurns())
    {
        if (controllField->getSkipped() && !controllField->searchPossibleTurns())
        {
            //todo Spiel beendet Grafik
            controllField->checkWin();
            std::cout << "Kein Spieler kann mehr ziehen, Spiel beendet." << std::endl;
        }
        else
        {
            controllField->skipTurn();
            mainUI->label->setText(QString::fromStdString(controllField->getInfoText()));
        }
    }
    else
    {
        std::cout << "Fehler, Zug möglich oder Spiel nicht gestartet." << std::endl;
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    mainUI->graphicsViewField->viewport()->removeEventFilter(this);
    /*mainUI->graphicsViewField->setScene(myMenu);
    if (!menuIsInit) {
        menuIsInit = true;
        myMenu->addOptionElements();
    }*/
    gameUI->setupUi(this);

    std::cout << "Optionen gedrückt" << std::endl;
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {

        QMouseEvent *me = static_cast<QMouseEvent *>(event);
        QPoint coordinates = me->pos();
        if (controllField->evaluateClick(coordinates.x(), coordinates.y()))
        {
            mainUI->label->setText(QString::fromStdString(controllField->getInfoText()));
            mainUI->labelPlayer1->setText(QString::fromStdString(controllField->getPlayer1Text()));
            mainUI->labelPlayer2->setText(QString::fromStdString(controllField->getPlayer2Text()));
        }


        return true;
    }
    if (event->type() == QEvent::Resize)
    {

        controllField->setFieldSize(mainUI->graphicsViewField->width(), mainUI->graphicsViewField->height());
        controllField->drawField();
    }

    return false;
}

