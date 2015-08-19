#include "mainwindow.h"
#include <iostream>
#include <string>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mainUI(new Ui::MainWindow), gameWidget(new Ui::GameWidget), menuWidget(new Ui::MenuWidget), pvpWidget(new Ui::PvPWidget)
{
    mainUI->setupUi(this);

    controllField = new controllerField();
    myMenu = new menu();
    myMenu->addOptionElements();

    menuWidget->setupUi(menuContainer);
    gameWidget->setupUi(gameContainer);
    pvpWidget->setupUi(pvpContainer);

    this->connect(menuWidget->pushButton_Start, SIGNAL(clicked()), this, SLOT(on_pushButton_Start_clicked()));
    this->connect(menuWidget->pushButton_StartAI, SIGNAL(clicked()), this, SLOT(on_pushButton_StartAI_clicked()));
    this->connect(menuWidget->pushButton_optionsMenu, SIGNAL(clicked()), this, SLOT(on_pushButton_optionsMenu_clicked()));

    mainUI->gridLayout->addWidget(menuContainer);

    playList = new QMediaPlaylist;
    playList->addMedia(QUrl("qrc:/music/Track01.mp3"));
    playList->addMedia(QUrl("qrc:/music/Track02.mp3"));
    playList->addMedia(QUrl("qrc:/music/Track03.mp3"));
    playList->addMedia(QUrl("qrc:/music/Track04.mp3"));
    playList->setCurrentIndex(1);

    player = new QMediaPlayer;
    player->setPlaylist(playList);

    player->setVolume(100);
    player->play();

}

MainWindow::~MainWindow()
{
    delete mainUI;
}


void MainWindow::on_pushButton_clicked()
{
    gameWidget->graphicsViewField->setScene(controllField->passViewField());
    controllField->initControllerField(4, myMenu->designSlider->value());
    gameWidget->label->setText(QString::fromStdString(controllField->getInfoText()));
    gameWidget->labelPlayer1->setText(QString::fromStdString(controllField->getPlayer1Text()));
    gameWidget->labelPlayer2->setText(QString::fromStdString(controllField->getPlayer2Text()));
    std::cout << "Text 1 " + controllField->getPlayer1Text() << std::endl;
    std::cout << "Text 2 " + controllField->getPlayer2Text() << std::endl;
    std::cout << "SetFieldSize to " + std::to_string(gameWidget->graphicsViewField->width()) + " x " + std::to_string(gameWidget->graphicsViewField->height()) << std::endl;
    controllField->setFieldSize(gameWidget->graphicsViewField->width(), gameWidget->graphicsViewField->height());
    controllField->startGame();
    controllField->drawField();
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

//IngameOption Menu
void MainWindow::on_pushButton_3_clicked()
{
    if (ingameOptionOn)
    {
        this->disconnect(myMenu->volSlider, SIGNAL(valueChanged(int)), this, SLOT(changeVolume(int)));
        this->disconnect(myMenu->volOnOff, SIGNAL(toggled(bool)), this, SLOT(toggleVolume(bool)));
        this->disconnect(myMenu->designSlider, SIGNAL(valueChanged(int)), this, SLOT(changeDesign(int)));
        gameWidget->pushButton_3->setText("Optionen");
        gameWidget->graphicsViewField->setScene(controllField->passViewField());
        gameWidget->graphicsViewField->viewport()->installEventFilter(this);
        ingameOptionOn = false;
    }
    else {
        gameWidget->pushButton_3->setText("Zurück");
        gameWidget->graphicsViewField->viewport()->removeEventFilter(this);
        gameWidget->graphicsViewField->setScene(myMenu);
        this->connect(myMenu->volSlider, SIGNAL(valueChanged(int)), this, SLOT(changeVolume(int)));
        this->connect(myMenu->volOnOff, SIGNAL(toggled(bool)), this, SLOT(toggleVolume(bool)));
        this->connect(myMenu->designSlider, SIGNAL(valueChanged(int)), this, SLOT(changeDesign(int)));
        ingameOptionOn = true;
    }


    std::cout << "Optionen (ingame) gedrückt" << std::endl;
}

void MainWindow::changeVolume(int value)
{
    std::cout << "Volume = " + std::to_string(myMenu->volSlider->value()) << std::endl;
    player->setVolume(value);
}

void MainWindow::toggleVolume(bool checked)
{
    std::cout << "toggleVol = " + std::to_string(checked) << std::endl;
    if (checked) {
        player->setVolume(myMenu->volSlider->value());
    }
    else {
        player->setVolume(0);
    }
}

void MainWindow::changeDesign(int design)
{
    std::cout << "Design = " + std::to_string(myMenu->designSlider->value()) << std::endl;
    controllField->setDesign(design);
}


bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
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
        std::cout << "Resize erkannt" << std::endl;
    }

    return false;
}

void MainWindow::on_pushButton_Start_clicked()
{
    this->disconnect(menuWidget->pushButton_Start, SIGNAL(clicked()), this, SLOT(on_pushButton_Start_clicked()));
    this->disconnect(menuWidget->pushButton_StartAI, SIGNAL(clicked()), this, SLOT(on_pushButton_StartAI_clicked()));
    this->disconnect(menuWidget->pushButton_optionsMenu, SIGNAL(clicked()), this, SLOT(on_pushButton_optionsMenu_clicked()));
    std::cout << "Start gedrückt" << std::endl;
    mainUI->gridLayout->removeWidget(menuContainer);
    mainUI->gridLayout->addWidget(pvpContainer);
    this->connect(pvpWidget->pushButton_StartPvP, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_StartPvP_clicked()));

}

void MainWindow::on_pushButton_StartAI_clicked()
{
    std::cout << "Start AI gedrückt" << std::endl;

    this->disconnect(menuWidget->pushButton_Start, SIGNAL(clicked()), this, SLOT(on_pushButton_Start_clicked()));
    this->disconnect(menuWidget->pushButton_StartAI, SIGNAL(clicked()), this, SLOT(on_pushButton_StartAI_clicked()));
    this->disconnect(menuWidget->pushButton_optionsMenu, SIGNAL(clicked()), this, SLOT(on_pushButton_optionsMenu_clicked()));

    this->connect(gameWidget->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    this->connect(gameWidget->pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_2_clicked()));
    this->connect(gameWidget->pushButton_3, SIGNAL(clicked()), this, SLOT(on_pushButton_3_clicked()));

    mainUI->gridLayout->removeWidget(menuContainer);
    mainUI->gridLayout->addWidget(gameContainer);


    controllField->initControllerField(4, myMenu->designSlider->value());
    gameWidget->label->setText(QString::fromStdString(controllField->getInfoText()));
    gameWidget->labelPlayer1->setText(QString::fromStdString(controllField->getPlayer1Text()));
    gameWidget->labelPlayer2->setText(QString::fromStdString(controllField->getPlayer2Text()));
    std::cout << "Text 1 " + controllField->getPlayer1Text() << std::endl;
    std::cout << "Text 2 " + controllField->getPlayer2Text() << std::endl;
    gameWidget->graphicsViewField->viewport()->installEventFilter(this);
    gameWidget->graphicsViewField->setScene(controllField->passViewField());
    std::cout << "SetFieldSize to " + std::to_string(gameWidget->graphicsViewField->width()) + " x " + std::to_string(gameWidget->graphicsViewField->height()) << std::endl;
    controllField->setFieldSize(gameWidget->graphicsViewField->width(), gameWidget->graphicsViewField->height());
    controllField->startGame();
    controllField->drawField();
}

void MainWindow::on_pushButton_optionsMenu_clicked()
{
    std::cout << "Optionen gedrückt" << std::endl;
}





void MainWindow::on_pushButton_StartPvP_clicked()
{
    std::string player1Name = pvpWidget->lineEdit_Player1->text().toStdString();
    std::string player2Name = pvpWidget->lineEdit_Player2->text().toStdString();

    if (player1Name == "" || player1Name.length() < 2)
    {
        player1Name = "Spieler 1";
    }
    if (player2Name == "" || player2Name.length() < 2)
    {
        player2Name = "Spieler 2";
    }

    this->connect(gameWidget->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    this->connect(gameWidget->pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_2_clicked()));
    this->connect(gameWidget->pushButton_3, SIGNAL(clicked()), this, SLOT(on_pushButton_3_clicked()));

    mainUI->gridLayout->removeWidget(pvpContainer);
    mainUI->gridLayout->addWidget(gameContainer);


    controllField->initControllerField(4, myMenu->designSlider->value());

    controllField->setPlayer1Name(player1Name);
    controllField->setPlayer2Name(player2Name);
    controllField->setShowPossTurns(pvpWidget->checkBox_showPossMoves->isChecked());

    gameWidget->label->setText(QString::fromStdString(controllField->getInfoText()));
    gameWidget->labelPlayer1->setText(QString::fromStdString(controllField->getPlayer1Text()));
    gameWidget->labelPlayer2->setText(QString::fromStdString(controllField->getPlayer2Text()));
    std::cout << "Text 1 " + controllField->getPlayer1Text() << std::endl;
    std::cout << "Text 2 " + controllField->getPlayer2Text() << std::endl;
    gameWidget->graphicsViewField->viewport()->installEventFilter(this);
    gameWidget->graphicsViewField->setScene(controllField->passViewField());
    std::cout << "SetFieldSize to " + std::to_string(gameWidget->graphicsViewField->width()) + " x " + std::to_string(gameWidget->graphicsViewField->height()) << std::endl;
    controllField->setFieldSize(gameWidget->graphicsViewField->width(), gameWidget->graphicsViewField->height());
    controllField->startGame();
    controllField->drawField();
}
