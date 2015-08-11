#include "mainwindow.h"
#include <iostream>
#include <string>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mainUI(new Ui::MainWindow), gameWidget(new Ui::GameWidget), menuWidget(new Ui::MenuWidget)
{
    mainUI->setupUi(this);

    controllField = new controllerField();
    myMenu = new menu();

    menuWidget->setupUi(menuContainer);
    this->connect(menuWidget->pushButton_Start, SIGNAL(clicked()), this, SLOT(on_pushButton_Start_clicked()));
    this->connect(menuWidget->pushButton_optionsMenu, SIGNAL(clicked()), this, SLOT(on_pushButton_optionsMenu_clicked()));
    gameWidget->setupUi(gameContainer);
    mainUI->gridLayout->addWidget(menuContainer);
    //menuContainer->installEventFilter();

    //ui->graphicsViewField->fitInView(controllField->passViewField()->sceneRect());

}

MainWindow::~MainWindow()
{
    delete mainUI;
}


void MainWindow::on_pushButton_clicked()
{
    gameWidget->graphicsViewField->setScene(controllField->passViewField());
    controllField->initControllerField(4, gameWidget->graphicsViewField->width(), gameWidget->graphicsViewField->height());
    gameWidget->label->setText(QString::fromStdString(controllField->getInfoText()));
    gameWidget->labelPlayer1->setText(QString::fromStdString(controllField->getPlayer1Text()));
    gameWidget->labelPlayer2->setText(QString::fromStdString(controllField->getPlayer2Text()));
    std::cout << "Text 1 " + controllField->getPlayer1Text() << std::endl;
    std::cout << "Text 2 " + controllField->getPlayer2Text() << std::endl;
    std::cout << "SetFieldSize to " + std::to_string(gameWidget->graphicsViewField->width()) + " x " + std::to_string(gameWidget->graphicsViewField->height()) << std::endl;
    gameWidget->graphicsViewField->viewport()->installEventFilter(this);

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
            gameWidget->label->setText(QString::fromStdString(controllField->getInfoText()));
        }
    }
    else
    {
        std::cout << "Fehler, Zug möglich oder Spiel nicht gestartet." << std::endl;
    }
}
/*
void MainWindow::on_pushButton_3_clicked()
{
    gameWidget->graphicsViewField->viewport()->removeEventFilter(this);
    mainUI->graphicsViewField->setScene(myMenu);
    if (!menuIsInit) {
        menuIsInit = true;
        myMenu->addOptionElements();
    }

    std::cout << "Optionen gedrückt" << std::endl;
}
*/


bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        std::cout << target->objectName().toStdString() << std::endl;

        QMouseEvent *me = static_cast<QMouseEvent *>(event);
        QPoint coordinates = me->pos();
        if (controllField->evaluateClick(coordinates.x(), coordinates.y()))
        {
            gameWidget->label->setText(QString::fromStdString(controllField->getInfoText()));
            gameWidget->labelPlayer1->setText(QString::fromStdString(controllField->getPlayer1Text()));
            gameWidget->labelPlayer2->setText(QString::fromStdString(controllField->getPlayer2Text()));
        }


        return true;
    }
    if (event->type() == QEvent::Resize)
    {

        controllField->setFieldSize(gameWidget->graphicsViewField->width(), gameWidget->graphicsViewField->height());
        controllField->drawField();
    }

    return false;
}

void MainWindow::on_pushButton_Start_clicked()
{
    std::cout << "Start gedrückt" << std::endl;
    this->connect(gameWidget->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    this->connect(gameWidget->pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_2_clicked()));
    mainUI->gridLayout->removeWidget(menuContainer);
    mainUI->gridLayout->addWidget(gameContainer);

}

void MainWindow::on_pushButton_optionsMenu_clicked()
{
    std::cout << "Optionen gedrückt" << std::endl;
}
