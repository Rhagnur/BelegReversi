#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    controllField = new controllerField();
    myMenu = new menu();

    //ui->graphicsViewField->fitInView(controllField->passViewField()->sceneRect());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->graphicsViewField->setScene(controllField->passViewField());
    controllField->initControllerField(4, ui->graphicsViewField->width(), ui->graphicsViewField->height());
    ui->label->setText(QString::fromStdString(controllField->getInfoText()));
    ui->labelPlayer1->setText(QString::fromStdString(controllField->getPlayer1Text()));
    ui->labelPlayer2->setText(QString::fromStdString(controllField->getPlayer2Text()));
    std::cout << "Text 1 " + controllField->getPlayer1Text() << std::endl;
    std::cout << "Text 2 " + controllField->getPlayer2Text() << std::endl;
    std::cout << "SetFieldSize to " + std::to_string(ui->graphicsViewField->width()) + " x " + std::to_string(ui->graphicsViewField->height()) << std::endl;
    ui->graphicsViewField->viewport()->installEventFilter(this);

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
            ui->label->setText(QString::fromStdString(controllField->getInfoText()));
        }
    }
    else
    {
        std::cout << "Fehler, Zug möglich oder Spiel nicht gestartet." << std::endl;
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->graphicsViewField->viewport()->removeEventFilter(this);
    ui->graphicsViewField->setScene(myMenu);
    if (!menuIsInit) {
        menuIsInit = true;
        myMenu->addOptionElements();
    }

    std::cout << "Optionen gedrückt" << std::endl;
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {

        QMouseEvent *me = static_cast<QMouseEvent *>(event);
        QPoint coordinates = me->pos();
        if (controllField->evaluateClick(coordinates.x(), coordinates.y()))
        {
            ui->label->setText(QString::fromStdString(controllField->getInfoText()));
            ui->labelPlayer1->setText(QString::fromStdString(controllField->getPlayer1Text()));
            ui->labelPlayer2->setText(QString::fromStdString(controllField->getPlayer2Text()));
        }


        return true;
    }
    if (event->type() == QEvent::Resize)
    {

        controllField->setFieldSize(ui->graphicsViewField->width(), ui->graphicsViewField->height());
        controllField->drawField();
    }

    return false;
}

