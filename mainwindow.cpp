#include "mainwindow.h"
#include <iostream>
#include <string>
#include <QDialog>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mainUI(new Ui::MainWindow), gameWidget(new Ui::GameWidget), menuWidget(new Ui::MenuWidget), pvpWidget(new Ui::PvPWidget), hsWidget(new Ui::HSWidget), optionWidget(new Ui::OptionWidget)
{
    mainUI->setupUi(this);

    controllField = new controllerField();

    myMenu = new menu();
    myMenu->addOptionElements();

    hsField = new ViewHS();

    menuWidget->setupUi(menuContainer);
    gameWidget->setupUi(gameContainer);    
    hsWidget->setupUi(hsContainer);
    pvpWidget->setupUi(pvpContainer);
    optionWidget->setupUi(optionContainer);

    pvpWidget->comboBox_PvPFieldsize->addItem("4x4", QVariant(4));
    pvpWidget->comboBox_PvPFieldsize->addItem("6x6", QVariant(6));
    pvpWidget->comboBox_PvPFieldsize->addItem("8x8", QVariant(8));
    pvpWidget->comboBox_PvPFieldsize->addItem("10x10", QVariant(10));
    pvpWidget->comboBox_PvPFieldsize->setCurrentIndex(2);
    pvpWidget->comboBox_PvPGamemode->addItem(tr("normal"));
    pvpWidget->comboBox_PvPGamemode->addItem(tr("Bo3"));
    pvpWidget->comboBox_PvPGamemode->addItem(tr("Bo5"));
    pvpWidget->comboBox_PvPGamemode->addItem(tr("Under Pressure"));

    optionWidget->comboBox_OptionSprache->addItem("Deutsch", QVariant("de"));
    optionWidget->comboBox_OptionSprache->addItem("English", QVariant("eng"));
    optionWidget->comboBox_OptionDesign->addItem("Klassisch", QVariant(1));
    optionWidget->comboBox_OptionDesign->addItem("Love", QVariant(2));
    optionWidget->comboBox_OptionDesign->addItem("Blabla", QVariant(3));



    this->connect(menuWidget->pushButton_StartPvP, SIGNAL(clicked()), this, SLOT(on_pushButton_StartPvP_clicked()));
    this->connect(menuWidget->pushButton_StartAI, SIGNAL(clicked()), this, SLOT(on_pushButton_StartAI_clicked()));
    this->connect(menuWidget->pushButton_optionsMenu, SIGNAL(clicked()), this, SLOT(on_pushButton_optionsMenu_clicked()));
    this->connect(menuWidget->pushButton_Highscore, SIGNAL(clicked()), this, SLOT(on_pushButton_Highscore_clicked()));

    mainUI->gridLayout->addWidget(menuContainer);
    menuContainer->show();

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


void MainWindow::on_pushButton_IngameBack_clicked()
{
    this->disconnect(gameWidget->pushButton_IngameBack, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameBack_clicked()));
    this->disconnect(gameWidget->pushButton_IngameSkip, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameSkip_clicked()));
    this->disconnect(gameWidget->pushButton_IngameOptions, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameOptions_clicked()));
    mainUI->gridLayout->removeWidget(gameContainer);
    gameContainer->hide();
    mainUI->gridLayout->addWidget(menuContainer);
    menuContainer->show();
    this->connect(menuWidget->pushButton_StartPvP, SIGNAL(clicked()), this, SLOT(on_pushButton_StartPvP_clicked()));
    this->connect(menuWidget->pushButton_StartAI, SIGNAL(clicked()), this, SLOT(on_pushButton_StartAI_clicked()));
    this->connect(menuWidget->pushButton_optionsMenu, SIGNAL(clicked()), this, SLOT(on_pushButton_optionsMenu_clicked()));
    this->connect(menuWidget->pushButton_Highscore, SIGNAL(clicked()), this, SLOT(on_pushButton_Highscore_clicked()));
}

void MainWindow::on_pushButton_IngameSkip_clicked()
{
    if(controllField->isInit && !controllField->searchPossibleTurns())
    {
        if (controllField->getSkipped() && !controllField->searchPossibleTurns())
        {
            controllField->checkWin();
        }
        else
        {
            controllField->skipTurn();
            //gameWidget->label->setText(QString::fromStdString(controllField->getInfoText()));
        }
    }
}

//IngameOption Menu noch deutlich besser machen!
void MainWindow::on_pushButton_IngameOptions_clicked()
{
    this->disconnect(gameWidget->pushButton_IngameBack, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameBack_clicked()));
    this->disconnect(gameWidget->pushButton_IngameSkip, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameSkip_clicked()));
    this->disconnect(gameWidget->pushButton_IngameOptions, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameOptions_clicked()));
    mainUI->gridLayout->removeWidget(gameContainer);
    gameContainer->hide();
    mainUI->gridLayout->addWidget(optionContainer);
    optionContainer->show();
    this->connect(optionWidget->pushButton_OptionBack, SIGNAL(clicked()), this, SLOT(on_pushButton_OptionBack_clicked()));
    this->connect(optionWidget->pushButton_OptionMusikLoad, SIGNAL(clicked()), this, SLOT(on_pushButton_OptionMusikLoad_clicked()));
    this->connect(optionWidget->horizontalSlider_OptionVolume, SIGNAL(valueChanged(int)), this, SLOT(changeVolume(int)));
    this->connect(optionWidget->checkBox, SIGNAL(toggled(bool)), this, SLOT(toggleVolume(bool)));
    ingameOptionOn = true;
}

void MainWindow::changeVolume(int value)
{
    player->setVolume(value);
}

void MainWindow::toggleVolume(bool checked)
{
    if (!checked) {
        player->setVolume(myMenu->volSlider->value());
    }
    else {
        player->setVolume(0);
    }
}

void MainWindow::changeDesign(int design)
{
    controllField->setDesign(design);
}


bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *me = static_cast<QMouseEvent *>(event);
        QPoint coordinates = me->pos();
        if (controllField->evaluateClick(coordinates.x(), coordinates.y()))
        {
            //gameWidget->label->setText(QString::fromStdString(controllField->getInfoText()));
            //gameWidget->label->update();
            //gameWidget->labelPlayer1->setText(QString::fromStdString(controllField->getPlayer1Text()));
            //gameWidget->labelPlayer2->setText(QString::fromStdString(controllField->getPlayer2Text()));
            std::cout << "Click" << std::endl;
        }
        //gameWidget->graphicsViewField->setGeometry(offset,48,w,h);
        return true;
    }
    if (event->type() == QEvent::Resize)
    {
        w = gameWidget->graphicsViewField->width();
        h = gameWidget->graphicsViewField->height();
        offset = 0;
        if (w > h) {
            w = h;
        }
        if (h > w) {
            h = w;
        }
        offset = (this->width() - w) / 2;
        offset -= 10;
        gameWidget->graphicsViewField->setGeometry(offset,48,w,h);
        std::cout << "Resize: " + std::to_string(this->width()) + " - " + std::to_string(w) << std::endl;
        controllField->setFieldSize(w, h);
        controllField->clearField();
        controllField->drawField();
        return true;
    }

    return false;
}

void MainWindow::on_pushButton_StartPvP_clicked()
{
    this->disconnect(menuWidget->pushButton_StartPvP, SIGNAL(clicked()), this, SLOT(on_pushButton_StartPvP_clicked()));
    this->disconnect(menuWidget->pushButton_StartAI, SIGNAL(clicked()), this, SLOT(on_pushButton_StartAI_clicked()));
    this->disconnect(menuWidget->pushButton_optionsMenu, SIGNAL(clicked()), this, SLOT(on_pushButton_optionsMenu_clicked()));
    mainUI->gridLayout->removeWidget(menuContainer);
    menuContainer->hide();
    mainUI->gridLayout->addWidget(pvpContainer);
    pvpContainer->show();
    this->connect(pvpWidget->pushButton_StartGamePvP, SIGNAL(clicked()), this, SLOT(on_pushButton_StartGamePvP_clicked()));
    this->connect(pvpWidget->pushButton_BackPVP, SIGNAL(clicked()), this, SLOT(on_pushButton_BackPVP_clicked()));

}

void MainWindow::on_pushButton_StartAI_clicked()
{
    this->disconnect(menuWidget->pushButton_StartPvP, SIGNAL(clicked()), this, SLOT(on_pushButton_StartPvP_clicked()));
    this->disconnect(menuWidget->pushButton_StartAI, SIGNAL(clicked()), this, SLOT(on_pushButton_StartAI_clicked()));
    this->disconnect(menuWidget->pushButton_optionsMenu, SIGNAL(clicked()), this, SLOT(on_pushButton_optionsMenu_clicked()));

    this->connect(gameWidget->pushButton_IngameBack, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameBack_clicked()));
    this->connect(gameWidget->pushButton_IngameSkip, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameSkip_clicked()));
    this->connect(gameWidget->pushButton_IngameOptions, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameOptions_clicked()));

    mainUI->gridLayout->removeWidget(menuContainer);
    menuContainer->hide();
    mainUI->gridLayout->addWidget(gameContainer);
    gameContainer->show();


    controllField->initControllerField(4, myMenu->designSlider->value());
    //gameWidget->label->setText(QString::fromStdString(controllField->getInfoText()));
    gameWidget->labelPlayer1->setText(pvpWidget->lineEdit_Player1->text());
    gameWidget->labelPlayer2->setText(pvpWidget->lineEdit_Player2->text());
    gameWidget->graphicsViewField->viewport()->installEventFilter(this);
    gameWidget->graphicsViewField->setScene(controllField->passViewField());
    std::cout << "SetFieldSize to " + std::to_string(gameWidget->graphicsViewField->width()) + " x " + std::to_string(gameWidget->graphicsViewField->height()) << std::endl;
    controllField->setFieldSize(gameWidget->graphicsViewField->width(), gameWidget->graphicsViewField->height());
    controllField->startGame();
    controllField->drawField();
}

void MainWindow::on_pushButton_optionsMenu_clicked()
{
    this->disconnect(menuWidget->pushButton_StartPvP, SIGNAL(clicked()), this, SLOT(on_pushButton_StartPvP_clicked()));
    this->disconnect(menuWidget->pushButton_StartAI, SIGNAL(clicked()), this, SLOT(on_pushButton_StartAI_clicked()));
    this->disconnect(menuWidget->pushButton_optionsMenu, SIGNAL(clicked()), this, SLOT(on_pushButton_optionsMenu_clicked()));
    this->disconnect(menuWidget->pushButton_Highscore, SIGNAL(clicked()), this, SLOT(on_pushButton_Highscore_clicked()));
    mainUI->gridLayout->removeWidget(menuContainer);
    menuContainer->hide();
    mainUI->gridLayout->addWidget(optionContainer);
    optionContainer->show();
    this->connect(optionWidget->pushButton_OptionBack, SIGNAL(clicked()), this, SLOT(on_pushButton_OptionBack_clicked()));
    this->connect(optionWidget->pushButton_OptionMusikLoad, SIGNAL(clicked()), this, SLOT(on_pushButton_OptionMusikLoad_clicked()));
    this->connect(optionWidget->horizontalSlider_OptionVolume, SIGNAL(valueChanged(int)), this, SLOT(changeVolume(int)));
    this->connect(optionWidget->checkBox, SIGNAL(toggled(bool)), this, SLOT(toggleVolume(bool)));
}





void MainWindow::on_pushButton_StartGamePvP_clicked()
{
    this->disconnect(pvpWidget->pushButton_StartGamePvP, SIGNAL(clicked()), this, SLOT(on_pushButton_StartGamePvP_clicked()));
    this->disconnect(pvpWidget->pushButton_BackPVP, SIGNAL(clicked()), this, SLOT(on_pushButton_BackPVP_clicked()));

    std::string player1Name = pvpWidget->lineEdit_Player1->text().toStdString();
    std::string player2Name = pvpWidget->lineEdit_Player2->text().toStdString();
    QVariant sizeVariant = pvpWidget->comboBox_PvPFieldsize->itemData(pvpWidget->comboBox_PvPFieldsize->currentIndex());
    int fieldSize = sizeVariant.toInt();

    if (player1Name == "" || player1Name.length() < 2)
    {
        player1Name = "Spieler 1";
    }
    if (player2Name == "" || player2Name.length() < 2)
    {
        player2Name = "Spieler 2";
    }

    this->connect(gameWidget->pushButton_IngameBack, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameBack_clicked()));
    this->connect(gameWidget->pushButton_IngameSkip, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameSkip_clicked()));
    this->connect(gameWidget->pushButton_IngameOptions, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameOptions_clicked()));

    mainUI->gridLayout->removeWidget(pvpContainer);
    pvpContainer->hide();
    mainUI->gridLayout->addWidget(gameContainer);
    gameContainer->show();


    controllField->initControllerField(fieldSize, myMenu->designSlider->value());

    controllField->setPlayer1Name(player1Name);
    controllField->setPlayer2Name(player2Name);
    controllField->setShowPossTurns(pvpWidget->checkBox_showPossMoves->isChecked());

    //gameWidget->label->setText(QString::fromStdString(controllField->getInfoText()));
    gameWidget->labelPlayer1->setText(pvpWidget->lineEdit_Player1->text());
    gameWidget->labelPlayer2->setText(pvpWidget->lineEdit_Player2->text());
    controllField->setLabelAndLCD(gameWidget->infoBox, gameWidget->lcdNumber_Player1, gameWidget->lcdNumber_Player2);
    gameWidget->graphicsViewField->setScene(controllField->passViewField());
    std::cout << "SetFieldSize to " + std::to_string(gameWidget->graphicsViewField->width()) + " x " + std::to_string(gameWidget->graphicsViewField->height()) << std::endl;
    controllField->setFieldSize(gameWidget->graphicsViewField->width(), gameWidget->graphicsViewField->height());
    controllField->startGame();
    controllField->drawField();
    gameWidget->graphicsViewField->viewport()->installEventFilter(this);
}

void MainWindow::on_pushButton_Highscore_clicked()
{
    this->disconnect(menuWidget->pushButton_StartPvP, SIGNAL(clicked()), this, SLOT(on_pushButton_StartPvP_clicked()));
    this->disconnect(menuWidget->pushButton_StartAI, SIGNAL(clicked()), this, SLOT(on_pushButton_StartAI_clicked()));
    this->disconnect(menuWidget->pushButton_optionsMenu, SIGNAL(clicked()), this, SLOT(on_pushButton_optionsMenu_clicked()));
    this->disconnect(menuWidget->pushButton_Highscore, SIGNAL(clicked()), this, SLOT(on_pushButton_Highscore_clicked()));
    mainUI->gridLayout->removeWidget(menuContainer);
    menuContainer->hide();
    mainUI->gridLayout->addWidget(hsContainer);
    hsContainer->show();
    this->connect(hsWidget->pushButton_HSBack, SIGNAL(clicked()), this, SLOT(on_pushButton_HSBack_clicked()));
    this->connect(hsWidget->pushButton_HSExport, SIGNAL(clicked()), this, SLOT(on_pushButton_HSExport_clicked()));
    hsWidget->graphicsViewHS->setScene(hsField->getViewField());
    hsField->clearField();
    hsField->drawText(controllField->getHighscore());
}

void MainWindow::on_pushButton_HSBack_clicked()
{
    this->disconnect(hsWidget->pushButton_HSBack, SIGNAL(clicked()), this, SLOT(on_pushButton_HSBack_clicked()));
    this->disconnect(hsWidget->pushButton_HSExport, SIGNAL(clicked()), this, SLOT(on_pushButton_HSExport_clicked()));
    mainUI->gridLayout->removeWidget(hsContainer);
    hsContainer->hide();
    mainUI->gridLayout->addWidget(menuContainer);
    menuContainer->show();
    this->connect(menuWidget->pushButton_StartPvP, SIGNAL(clicked()), this, SLOT(on_pushButton_StartPvP_clicked()));
    this->connect(menuWidget->pushButton_StartAI, SIGNAL(clicked()), this, SLOT(on_pushButton_StartAI_clicked()));
    this->connect(menuWidget->pushButton_optionsMenu, SIGNAL(clicked()), this, SLOT(on_pushButton_optionsMenu_clicked()));
    this->connect(menuWidget->pushButton_Highscore, SIGNAL(clicked()), this, SLOT(on_pushButton_Highscore_clicked()));
}

void MainWindow::on_pushButton_BackPVP_clicked()
{
    this->connect(pvpWidget->pushButton_StartGamePvP, SIGNAL(clicked()), this, SLOT(on_pushButton_StartGamePvP_clicked()));
    this->connect(pvpWidget->pushButton_BackPVP, SIGNAL(clicked()), this, SLOT(on_pushButton_BackPVP_clicked()));
    mainUI->gridLayout->removeWidget(pvpContainer);
    pvpContainer->hide();
    mainUI->gridLayout->addWidget(menuContainer);
    menuContainer->show();
    this->connect(menuWidget->pushButton_StartPvP, SIGNAL(clicked()), this, SLOT(on_pushButton_StartPvP_clicked()));
    this->connect(menuWidget->pushButton_StartAI, SIGNAL(clicked()), this, SLOT(on_pushButton_StartAI_clicked()));
    this->connect(menuWidget->pushButton_optionsMenu, SIGNAL(clicked()), this, SLOT(on_pushButton_optionsMenu_clicked()));
    this->connect(menuWidget->pushButton_Highscore, SIGNAL(clicked()), this, SLOT(on_pushButton_Highscore_clicked()));
}

void MainWindow::on_pushButton_HSExport_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Speichern als..."),
                                                  QString(), tr("TXT-Files (*.txt);;All Files (*)"));
    if (!filePath.endsWith(".txt"))
    {
        filePath += ".txt";
    }

    QFile exportFile(filePath);
    if (exportFile.exists())
    {
        exportFile.remove();
    }
    if (exportFile.open(QFile::Append))
    {
        QTextStream out(&exportFile);
        std::string buffer = controllField->getHighscore();
        std::replace(buffer.begin(), buffer.end(), '#', ' ');
        out << QString::fromStdString(buffer);
    }
}

void MainWindow::on_pushButton_OptionBack_clicked()
{
    if (ingameOptionOn) {
        this->disconnect(optionWidget->pushButton_OptionBack, SIGNAL(clicked()), this, SLOT(on_pushButton_OptionBack_clicked()));
        this->disconnect(optionWidget->pushButton_OptionMusikLoad, SIGNAL(clicked()), this, SLOT(on_pushButton_OptionMusikLoad_clicked()));
        this->disconnect(optionWidget->horizontalSlider_OptionVolume, SIGNAL(valueChanged(int)), this, SLOT(changeVolume(int)));
        this->disconnect(optionWidget->checkBox, SIGNAL(toggled(bool)), this, SLOT(toggleVolume(bool)));
        mainUI->gridLayout->removeWidget(optionContainer);
        optionContainer->hide();
        mainUI->gridLayout->addWidget(gameContainer);
        gameContainer->show();
        this->connect(gameWidget->pushButton_IngameBack, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameBack_clicked()));
        this->connect(gameWidget->pushButton_IngameSkip, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameSkip_clicked()));
        this->connect(gameWidget->pushButton_IngameOptions, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameOptions_clicked()));
        ingameOptionOn = false;
    }
    else {
        this->disconnect(optionWidget->pushButton_OptionBack, SIGNAL(clicked()), this, SLOT(on_pushButton_OptionBack_clicked()));
        this->disconnect(optionWidget->pushButton_OptionMusikLoad, SIGNAL(clicked()), this, SLOT(on_pushButton_OptionMusikLoad_clicked()));
        this->disconnect(optionWidget->horizontalSlider_OptionVolume, SIGNAL(valueChanged(int)), this, SLOT(changeVolume(int)));
        this->disconnect(optionWidget->checkBox, SIGNAL(toggled(bool)), this, SLOT(toggleVolume(bool)));
        mainUI->gridLayout->removeWidget(optionContainer);
        optionContainer->hide();
        mainUI->gridLayout->addWidget(menuContainer);
        menuContainer->show();
        this->connect(menuWidget->pushButton_StartPvP, SIGNAL(clicked()), this, SLOT(on_pushButton_StartPvP_clicked()));
        this->connect(menuWidget->pushButton_StartAI, SIGNAL(clicked()), this, SLOT(on_pushButton_StartAI_clicked()));
        this->connect(menuWidget->pushButton_optionsMenu, SIGNAL(clicked()), this, SLOT(on_pushButton_optionsMenu_clicked()));
        this->connect(menuWidget->pushButton_Highscore, SIGNAL(clicked()), this, SLOT(on_pushButton_Highscore_clicked()));
    }

}

void MainWindow::on_pushButton_OptionMusikLoad_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Laden"), QString(), tr("MP3-Files (*.mp3)"));
    if (files.length() > 0) {
        std::cout << "Musik laden" << std::endl;
        player->stop();
        playList->clear();
        for (QString file : files) {
            std::cout << "add " + file.toStdString() << std::endl;
            playList->addMedia(QUrl::fromLocalFile(file));
        }
        player->play();
    }

}
