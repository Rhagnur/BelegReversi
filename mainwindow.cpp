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


    dict = new MyDict();
    controllField = new controllerField();
    controllField->changeDict(dict->getDict("deu"));

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

    optionWidget->comboBox_OptionSprache->addItem("Deutsch");
    optionWidget->comboBox_OptionSprache->addItem("English");
    optionWidget->comboBox_OptionDesign->addItem("Classic");
    optionWidget->comboBox_OptionDesign->addItem("Love");
    optionWidget->comboBox_OptionDesign->addItem("Blabla");

    gameWidget->infoBox->setReadOnly(true);

    hsWidget->comboBox_HSSotieren->addItem("normal", QVariant(1));
    hsWidget->comboBox_HSSotieren->addItem("Feldgröße 4", QVariant(2));
    hsWidget->comboBox_HSSotieren->addItem("Feldgröße 6", QVariant(3));
    hsWidget->comboBox_HSSotieren->addItem("Feldgröße 8", QVariant(4));
    hsWidget->comboBox_HSSotieren->addItem("Feldgröße 10", QVariant(5));



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
    this->connect(optionWidget->comboBox_OptionDesign, SIGNAL(activated(int)), this, SLOT(changeDesign(int)));
    optionWidget->label_OptionSprache->hide();
    optionWidget->comboBox_OptionSprache->hide();
    ingameOptionOn = true;
}

void MainWindow::changeVolume(int value)
{
    player->setVolume(value);
}

void MainWindow::toggleVolume(bool checked)
{
    if (!checked) {
        player->setVolume(optionWidget->horizontalSlider_OptionVolume->value());
    }
    else {
        player->setVolume(0);
    }
}

void MainWindow::changeDesign(int design)
{
    std::cout << "[INFO] Change design :" + std::to_string(design) << std::endl;
    this->design = design;
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


    controllField->initControllerField(4, design);
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
    this->connect(optionWidget->comboBox_OptionSprache, SIGNAL(activated(int)), this, SLOT(on_comboBox_OptionSprache_activated(int)));
    this->connect(optionWidget->comboBox_OptionDesign, SIGNAL(activated(int)), this, SLOT(changeDesign(int)));
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

    gameWidget->labelPlayer1->setText(pvpWidget->lineEdit_Player1->text());
    gameWidget->labelPlayer2->setText(pvpWidget->lineEdit_Player2->text());
    controllField->setLabelAndLCD(gameWidget->infoBox, gameWidget->lcdNumber_Player1, gameWidget->lcdNumber_Player2);
    controllField->setPlayer1Name(pvpWidget->lineEdit_Player1->text().toStdString());
    controllField->setPlayer2Name(pvpWidget->lineEdit_Player2->text().toStdString());
    controllField->initControllerField(fieldSize, design);

    controllField->setPlayer1Name(player1Name);
    controllField->setPlayer2Name(player2Name);
    controllField->setShowPossTurns(pvpWidget->checkBox_showPossMoves->isChecked());

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
    this->connect(hsWidget->comboBox_HSSotieren, SIGNAL(activated(int)), this, SLOT(on_comboBox_HSSotieren_activated(int)));
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
    QString filePath = QFileDialog::getSaveFileName(this, tr("Export Highscore(normal)"),
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
    this->disconnect(optionWidget->pushButton_OptionBack, SIGNAL(clicked()), this, SLOT(on_pushButton_OptionBack_clicked()));
    this->disconnect(optionWidget->pushButton_OptionMusikLoad, SIGNAL(clicked()), this, SLOT(on_pushButton_OptionMusikLoad_clicked()));
    this->disconnect(optionWidget->horizontalSlider_OptionVolume, SIGNAL(valueChanged(int)), this, SLOT(changeVolume(int)));
    this->disconnect(optionWidget->checkBox, SIGNAL(toggled(bool)), this, SLOT(toggleVolume(bool)));
    this->disconnect(optionWidget->comboBox_OptionSprache, SIGNAL(activated(int)), this, SLOT(on_comboBox_OptionSprache_activated(int)));
    this->disconnect(optionWidget->comboBox_OptionDesign, SIGNAL(activated(int)), this, SLOT(changeDesign(int)));
    mainUI->gridLayout->removeWidget(optionContainer);
    optionContainer->hide();

    if (ingameOptionOn) {
        optionWidget->label_OptionSprache->show();
        optionWidget->comboBox_OptionSprache->show();
        mainUI->gridLayout->addWidget(gameContainer);
        gameContainer->show();
        this->connect(gameWidget->pushButton_IngameBack, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameBack_clicked()));
        this->connect(gameWidget->pushButton_IngameSkip, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameSkip_clicked()));
        this->connect(gameWidget->pushButton_IngameOptions, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameOptions_clicked()));
        ingameOptionOn = false;
    }
    else {
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
        player->stop();
        playList->clear();
        for (QString file : files) {
            std::cout << "[INFO] Add to musicqueue: " + file.toStdString() << std::endl;
            playList->addMedia(QUrl::fromLocalFile(file));
        }
        player->play();
    }

}

void MainWindow::on_comboBox_HSSotieren_activated(int index)
{
    if(index == 0) {
        hsField->clearField();
        hsField->drawText(controllField->getHighscore());
    }
    if(index == 1) {
        hsField->clearField();
        hsField->drawText(controllField->getHighscoreBySize(4));
    }
    if(index == 2) {
        hsField->clearField();
        hsField->drawText(controllField->getHighscoreBySize(6));
    }
    if(index == 3) {
        hsField->clearField();
        hsField->drawText(controllField->getHighscoreBySize(8));
    }
    if(index == 4) {
        hsField->clearField();
        hsField->drawText(controllField->getHighscoreBySize(10));
    }
}

void MainWindow::on_comboBox_OptionSprache_activated(int index)
{

    std::string sprache = "";

    if (index == 0) {
        sprache = "deu";
    }
    else {
        sprache = "eng";
    }

    std::cout << "[INFO] Change language to " + sprache << std::endl;

    myDict = dict->getDict(sprache);
    controllField->changeDict(myDict);
    changeLanguage();
}

void MainWindow::changeLanguage()
{
    std::cout << "[INFO] Change text from elements" << std::endl;

    optionWidget->checkBox->setText(QString::fromStdString(myDict[24]));
    optionWidget->label_OptionDesign->setText(QString::fromStdString(myDict[3]));
    optionWidget->label_OptionMusikLoad->setText(QString::fromStdString(myDict[4]));
    optionWidget->label_OptionSprache->setText(QString::fromStdString(myDict[23]));
    optionWidget->label_OptionVolumeLevel->setText(QString::fromStdString(myDict[11]));
    optionWidget->label_OptionVolumeOnOff->setText(QString::fromStdString(myDict[14]));
    optionWidget->pushButton_OptionBack->setText(QString::fromStdString(myDict[27]));
    optionWidget->pushButton_OptionMusikLoad->setText(QString::fromStdString(myDict[13]));

    menuWidget->pushButton_Credits->setText(QString::fromStdString(myDict[2]));
    menuWidget->pushButton_Highscore->setText(QString::fromStdString(myDict[7]));
    menuWidget->pushButton_optionsMenu->setText(QString::fromStdString(myDict[17]));
    menuWidget->pushButton_StartAI->setText(QString::fromStdString(myDict[18]));
    menuWidget->pushButton_StartPvP->setText(QString::fromStdString(myDict[19]));

    gameWidget->pushButton_IngameBack->setText(QString::fromStdString(myDict[27]));
    gameWidget->pushButton_IngameOptions->setText(QString::fromStdString(myDict[17]));
    gameWidget->pushButton_IngameSkip->setText(QString::fromStdString(myDict[26]));

    hsWidget->label_HSSortieren->setText(QString::fromStdString(myDict[1]));
    hsWidget->label_HSTitle->setText(QString::fromStdString(myDict[7]));
    hsWidget->pushButton_HSBack->setText(QString::fromStdString(myDict[27]));
    hsWidget->pushButton_HSExport->setText(QString::fromStdString(myDict[5]));

    pvpWidget->checkBox_showPossMoves->setText(QString::fromStdString(myDict[0]));
    pvpWidget->pushButton_BackPVP->setText(QString::fromStdString(myDict[27]));
    pvpWidget->pushButton_StartGamePvP->setText(QString::fromStdString(myDict[22]));
    pvpWidget->label->setText(QString::fromStdString(myDict[20]));
    pvpWidget->label_GameMode->setText(QString::fromStdString(myDict[21]));
    pvpWidget->label_Player1->setText(QString::fromStdString(myDict[15]));
    pvpWidget->label_Player2->setText(QString::fromStdString(myDict[16]));
    pvpWidget->label_PossMoves->setText(QString::fromStdString(myDict[12]));
}
