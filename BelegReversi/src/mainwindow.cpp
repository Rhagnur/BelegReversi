#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mainUI(new Ui::MainWindow), gameWidget(new Ui::GameWidget), menuWidget(new Ui::MenuWidget), pvpWidget(new Ui::PvPWidget), hsWidget(new Ui::HSWidget), optionWidget(new Ui::OptionWidget), pvcWidget(new Ui::PvCWidget)
{
    mainUI->setupUi(this);

    timer = new QTimer(this);

    dict = new MyDict();
    myDict = dict->getDict("deu");
    controllField = new controllerField();
    controllField->changeDict(dict->getDict("deu"));

    hsField = new ViewHS();

    menuWidget->setupUi(menuContainer);
    gameWidget->setupUi(gameContainer);    
    hsWidget->setupUi(hsContainer);
    pvpWidget->setupUi(pvpContainer);
    optionWidget->setupUi(optionContainer);
    pvcWidget->setupUi(pvcContainer);

    pvpWidget->comboBox_PvPFieldsize->addItem("4x4", QVariant(4));
    pvpWidget->comboBox_PvPFieldsize->addItem("6x6", QVariant(6));
    pvpWidget->comboBox_PvPFieldsize->addItem("8x8", QVariant(8));
    pvpWidget->comboBox_PvPFieldsize->addItem("10x10", QVariant(10));
    pvpWidget->comboBox_PvPFieldsize->setCurrentIndex(2);
    pvpWidget->comboBox_PvPGamemode->addItem(tr("normal"));
    pvpWidget->comboBox_PvPGamemode->addItem(tr("Under Pressure"));

    pvcWidget->comboBox_PvCFieldsize->addItem("4x4", QVariant(4));
    pvcWidget->comboBox_PvCFieldsize->addItem("6x6", QVariant(6));
    pvcWidget->comboBox_PvCFieldsize->addItem("8x8", QVariant(8));
    pvcWidget->comboBox_PvCFieldsize->addItem("10x10", QVariant(10));
    pvcWidget->comboBox_PvCFieldsize->setCurrentIndex(2);
    pvcWidget->comboBox_PvCDifficulty->addItem(tr("easy"));
    pvcWidget->comboBox_PvCDifficulty->addItem(tr("normal"));
    pvcWidget->comboBox_PvCDifficulty->addItem(tr("hard"));
    pvcWidget->comboBox_PvCBeginnt->addItem("Player");
    pvcWidget->comboBox_PvCBeginnt->addItem("Computer");

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
    //playList->addMedia(QUrl("qrc:/music/Track01.mp3"));
    //playList->addMedia(QUrl("qrc:/music/Track02.mp3"));
    playList->addMedia(QUrl("qrc:/music/Track03.mp3"));
    //playList->addMedia(QUrl("qrc:/music/Track04.mp3"));
    playList->setCurrentIndex(1);

    player = new QMediaPlayer;
    player->setPlaylist(playList);

    player->setVolume(100);
    player->play();
}

MainWindow::~MainWindow()
{
    delete mainUI;
    delete gameWidget;
    delete pvpWidget;
    delete menuWidget;
    delete optionWidget;
    delete pvcWidget;
    delete hsWidget;
    delete hsField;
    delete player;
    delete playList;
    delete dict;
    delete timer;
    delete controllField;
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *me = static_cast<QMouseEvent *>(event);
        QPoint coordinates = me->pos();
        if (controllField->evaluateClick(coordinates.x(), coordinates.y()))
        {
            if (gameMode == 3)
            {
                if (controllField->checkWin()) {
                    timer->stop();
                }
                else {
                    timer->stop();
                    timeCount = 15;
                    timer->start(timePeriod);
                    gameWidget->infoBox->appendPlainText("15 " + myDict[28]);
                }

            }
            else
            {
                controllField->checkWin();
            }
        }
        return true;
    }
    if (event->type() == QEvent::Resize)
    {
        resizeMainWindow();
        return true;
    }

    return false;
}

void MainWindow::resizeMainWindow() {
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
    std::cout << "[INFO] Resize: " + QString::number(this->width()).toStdString() + " - " + QString::number(w).toStdString() << std::endl;
    controllField->setFieldSize(w, h);
    controllField->clearField();
    controllField->drawField();
}

void MainWindow::timeUp()
{
    timeCount -= 1;
    timer->start(timePeriod);
    if(timeCount == 0) {
        timer->stop();
        gameWidget->infoBox->clear();
        gameWidget->infoBox->appendPlainText(QString::number(timeCount) + " " + myDict[28]);
        controllField->timeUpWin();
        gameWidget->graphicsViewField->viewport()->removeEventFilter(this);
    }
    if(timeCount == 10 || timeCount == 5 || timeCount == 4 || timeCount == 3 || timeCount == 2 || timeCount == 1) {
        gameWidget->infoBox->clear();
        gameWidget->infoBox->appendPlainText(QString::number(timeCount) + " " + myDict[28]);
    }

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
    std::cout << "[INFO] Change design :" + QString::number(design).toStdString() << std::endl;
    this->design = design;
    controllField->setDesign(design);
}

void MainWindow::changeLanguage()
{
    std::cout << "[INFO] Change text from elements" << std::endl;

    optionWidget->checkBox->setText(myDict[24]);
    optionWidget->label_OptionDesign->setText(myDict[3]);
    optionWidget->label_OptionMusikLoad->setText(myDict[4]);
    optionWidget->label_OptionSprache->setText(myDict[23]);
    optionWidget->label_OptionVolumeLevel->setText(myDict[11]);
    optionWidget->label_OptionVolumeOnOff->setText(myDict[14]);
    optionWidget->pushButton_OptionBack->setText(myDict[27]);
    optionWidget->pushButton_OptionMusikLoad->setText(myDict[13]);

    //menuWidget->pushButton_Credits->setText(myDict[2]);
    menuWidget->pushButton_Highscore->setText(myDict[7]);
    menuWidget->pushButton_optionsMenu->setText(myDict[17]);
    menuWidget->pushButton_StartAI->setText(myDict[18]);
    menuWidget->pushButton_StartPvP->setText(myDict[19]);

    gameWidget->pushButton_IngameBack->setText(myDict[27]);
    gameWidget->pushButton_IngameOptions->setText(myDict[17]);
    gameWidget->pushButton_IngameSkip->setText(myDict[26]);

    hsWidget->label_HSSortieren->setText(myDict[1]);
    hsWidget->label_HSTitle->setText(myDict[7]);
    hsWidget->pushButton_HSBack->setText(myDict[27]);
    hsWidget->pushButton_HSExport->setText(myDict[5]);

    pvpWidget->checkBox_showPossMoves->setText(myDict[0]);
    pvpWidget->pushButton_BackPVP->setText(myDict[27]);
    pvpWidget->pushButton_StartGamePvP->setText(myDict[22]);
    pvpWidget->label->setText(myDict[20]);
    pvpWidget->label_GameMode->setText(myDict[21]);
    pvpWidget->label_Player1->setText(myDict[15]);
    pvpWidget->label_Player2->setText(myDict[16]);
    pvpWidget->label_PossMoves->setText(myDict[12]);

    pvcWidget->label_PvCSize->setText(myDict[20]);
    pvcWidget->label_PvCDifficulty->setText(myDict[29]);
    pvcWidget->label_PvCPossMoves->setText(myDict[12]);
    pvcWidget->label->setText(myDict[30]);
    pvcWidget->pushButton_BackPVC->setText(myDict[27]);
    pvcWidget->pushButton_StartGamePvC->setText(myDict[22]);
}

void MainWindow::on_pushButton_IngameBack_clicked()
{
    this->disconnect(gameWidget->pushButton_IngameBack, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameBack_clicked()));
    this->disconnect(gameWidget->pushButton_IngameSkip, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameSkip_clicked()));
    this->disconnect(gameWidget->pushButton_IngameOptions, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameOptions_clicked()));
    if (gameMode == 3) {
        this->disconnect(timer, SIGNAL(timeout()), this, SLOT(timeUp()));
        timer->stop();
    }
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
            if (controllField->checkWin()) {
                timer->stop();
            }
        }
        else
        {
            controllField->skipTurn();
            if (gameMode == 3) {
                timer->stop();
                timeCount = 15;
                timer->start(timePeriod);
                gameWidget->infoBox->appendPlainText("15 " + myDict[28]);
            }
        }
    }
}

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
    this->connect(optionWidget->checkBox_OptionVollbild, SIGNAL(clicked(bool)), this, SLOT(on_checkBox_OptionVollbild_clicked(bool)));
    optionWidget->label_OptionSprache->hide();
    optionWidget->comboBox_OptionSprache->hide();
    ingameOptionOn = true;
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
    this->connect(optionWidget->checkBox_OptionVollbild, SIGNAL(clicked(bool)), this, SLOT(on_checkBox_OptionVollbild_clicked(bool)));
}

void MainWindow::on_pushButton_OptionBack_clicked()
{
    this->disconnect(optionWidget->pushButton_OptionBack, SIGNAL(clicked()), this, SLOT(on_pushButton_OptionBack_clicked()));
    this->disconnect(optionWidget->pushButton_OptionMusikLoad, SIGNAL(clicked()), this, SLOT(on_pushButton_OptionMusikLoad_clicked()));
    this->disconnect(optionWidget->horizontalSlider_OptionVolume, SIGNAL(valueChanged(int)), this, SLOT(changeVolume(int)));
    this->disconnect(optionWidget->checkBox, SIGNAL(toggled(bool)), this, SLOT(toggleVolume(bool)));
    this->disconnect(optionWidget->comboBox_OptionSprache, SIGNAL(activated(int)), this, SLOT(on_comboBox_OptionSprache_activated(int)));
    this->disconnect(optionWidget->comboBox_OptionDesign, SIGNAL(activated(int)), this, SLOT(changeDesign(int)));
    this->disconnect(optionWidget->checkBox_OptionVollbild, SIGNAL(clicked(bool)), this, SLOT(on_checkBox_OptionVollbild_clicked(bool)));
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

void MainWindow::on_comboBox_OptionSprache_activated(int index)
{

    QString sprache = "";

    if (index == 0) {
        sprache = "deu";
    }
    else {
        sprache = "eng";
    }

    std::cout << "[INFO] Change language to " + sprache.toStdString() << std::endl;

    myDict = dict->getDict(sprache);
    controllField->changeDict(myDict);
    changeLanguage();
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
    this->connect(pvpWidget->comboBox_PvPGamemode, SIGNAL(activated(int)), this, SLOT(on_comboBox_PvPGamemode_activated(int)));

}

void MainWindow::on_pushButton_BackPVP_clicked()
{
    this->disconnect(pvpWidget->pushButton_StartGamePvP, SIGNAL(clicked()), this, SLOT(on_pushButton_StartGamePvP_clicked()));
    this->disconnect(pvpWidget->pushButton_BackPVP, SIGNAL(clicked()), this, SLOT(on_pushButton_BackPVP_clicked()));
    this->disconnect(pvpWidget->comboBox_PvPGamemode, SIGNAL(activated(int)), this, SLOT(on_comboBox_PvPGamemode_activated(int)));
    mainUI->gridLayout->removeWidget(pvpContainer);
    pvpContainer->hide();
    mainUI->gridLayout->addWidget(menuContainer);
    menuContainer->show();
    this->connect(menuWidget->pushButton_StartPvP, SIGNAL(clicked()), this, SLOT(on_pushButton_StartPvP_clicked()));
    this->connect(menuWidget->pushButton_StartAI, SIGNAL(clicked()), this, SLOT(on_pushButton_StartAI_clicked()));
    this->connect(menuWidget->pushButton_optionsMenu, SIGNAL(clicked()), this, SLOT(on_pushButton_optionsMenu_clicked()));
    this->connect(menuWidget->pushButton_Highscore, SIGNAL(clicked()), this, SLOT(on_pushButton_Highscore_clicked()));
}

void MainWindow::on_pushButton_StartGamePvP_clicked()
{
    this->disconnect(pvpWidget->pushButton_StartGamePvP, SIGNAL(clicked()), this, SLOT(on_pushButton_StartGamePvP_clicked()));
    this->disconnect(pvpWidget->pushButton_BackPVP, SIGNAL(clicked()), this, SLOT(on_pushButton_BackPVP_clicked()));
    this->disconnect(pvpWidget->comboBox_PvPGamemode, SIGNAL(activated(int)), this, SLOT(on_comboBox_PvPGamemode_activated(int)));

    QString player1Name = pvpWidget->lineEdit_Player1->text();
    QString player2Name = pvpWidget->lineEdit_Player2->text();
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

    gameWidget->labelPlayer1->setText(player1Name);
    gameWidget->labelPlayer2->setText(player2Name);
    controllField->setPlayer1Name(player1Name);
    controllField->setPlayer2Name(player2Name);
    controllField->setLabelAndLCD(gameWidget->infoBox, gameWidget->lcdNumber_Player1, gameWidget->lcdNumber_Player2);
    controllField->initControllerField(fieldSize, design);
    controllField->setShowPossTurns(pvpWidget->checkBox_showPossMoves->isChecked());

    gameWidget->graphicsViewField->setScene(controllField->getViewField());
    controllField->setFieldSize(gameWidget->graphicsViewField->width(), gameWidget->graphicsViewField->height());
    controllField->startGame();
    controllField->drawField();
    resizeMainWindow();


    if (gameMode == 1)
    {
        this->connect(timer, SIGNAL(timeout()), this, SLOT(timeUp()));
        timeCount = 15;
        timer->start(timePeriod);
        gameWidget->infoBox->appendPlainText("15 " + myDict[28]);
    }

    gameWidget->graphicsViewField->viewport()->installEventFilter(this);
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
    mainUI->gridLayout->addWidget(pvcContainer);
    pvcContainer->show();

    this->connect(pvcWidget->pushButton_StartGamePvC, SIGNAL(clicked()), this, SLOT(on_pushButton_StartGamePvC_clicked()));
    this->connect(pvcWidget->pushButton_BackPVC, SIGNAL(clicked()), this, SLOT(on_pushButton_BackPVC_clicked()));
}

void MainWindow::on_pushButton_StartGamePvC_clicked()
{
    this->disconnect(pvcWidget->pushButton_StartGamePvC, SIGNAL(clicked()), this, SLOT(on_pushButton_StartGamePvC_clicked()));
    this->disconnect(pvcWidget->pushButton_BackPVC, SIGNAL(clicked()), this, SLOT(on_pushButton_BackPVC_clicked()));

    QString playerName = pvcWidget->lineEdit_PvCPlayer->text();
    QVariant sizeVariant = pvcWidget->comboBox_PvCFieldsize->itemData(pvcWidget->comboBox_PvCFieldsize->currentIndex());
    int fieldSize = sizeVariant.toInt();

    if (playerName == "" || playerName.length() < 2)
    {
        playerName = "Spieler";
    }

    this->connect(gameWidget->pushButton_IngameBack, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameBack_clicked()));
    this->connect(gameWidget->pushButton_IngameSkip, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameSkip_clicked()));
    this->connect(gameWidget->pushButton_IngameOptions, SIGNAL(clicked()), this, SLOT(on_pushButton_IngameOptions_clicked()));

    mainUI->gridLayout->removeWidget(pvcContainer);
    pvcContainer->hide();
    mainUI->gridLayout->addWidget(gameContainer);
    gameContainer->show();

    QString beginner = pvcWidget->comboBox_PvCBeginnt->currentText(), diffculty = "";
    bool isAiFirst = false, isAiGame = true;
    int indexDifficulty = 0;

    if (beginner == "Spieler" || beginner == "Player") {
        gameWidget->labelPlayer1->setText(playerName);
        gameWidget->labelPlayer2->setText("Computer");
        controllField->setPlayer1Name(playerName);
        controllField->setPlayer2Name("Computer");
    }
    else {
        gameWidget->labelPlayer1->setText("Computer");
        gameWidget->labelPlayer2->setText(playerName);
        controllField->setPlayer2Name(playerName);
        controllField->setPlayer1Name("Computer");
        isAiFirst = true;

    }

    indexDifficulty = pvcWidget->comboBox_PvCDifficulty->currentIndex();
    if (indexDifficulty == 0) {
        diffculty = "easy";
    }
    else if (indexDifficulty == 1) {
        diffculty = "normal";
    }
    else {
        diffculty = "hard";
    }


    controllField->setLabelAndLCD(gameWidget->infoBox, gameWidget->lcdNumber_Player1, gameWidget->lcdNumber_Player2);
    controllField->initControllerField(fieldSize, design);
    controllField->setAiGame(isAiGame, isAiFirst);
    controllField->setShowPossTurns(pvcWidget->checkBox_PvCshowPossMoves->isChecked());
    controllField->setDifficulty(diffculty);

    gameWidget->graphicsViewField->setScene(controllField->getViewField());
    controllField->setFieldSize(gameWidget->graphicsViewField->width(), gameWidget->graphicsViewField->height());
    controllField->startGame();
    controllField->drawField();
    resizeMainWindow();

    gameWidget->graphicsViewField->viewport()->installEventFilter(this);
}

void MainWindow::on_pushButton_BackPVC_clicked()
{
    this->disconnect(pvcWidget->pushButton_StartGamePvC, SIGNAL(clicked()), this, SLOT(on_pushButton_StartGamePvC_clicked()));
    this->disconnect(pvcWidget->pushButton_BackPVC, SIGNAL(clicked()), this, SLOT(on_pushButton_BackPVC_clicked()));
    bool reset = false;
    controllField->setAiGame(reset, reset);
    mainUI->gridLayout->removeWidget(pvcContainer);
    pvcContainer->hide();
    mainUI->gridLayout->addWidget(menuContainer);
    menuContainer->show();
    this->connect(menuWidget->pushButton_StartPvP, SIGNAL(clicked()), this, SLOT(on_pushButton_StartPvP_clicked()));
    this->connect(menuWidget->pushButton_StartAI, SIGNAL(clicked()), this, SLOT(on_pushButton_StartAI_clicked()));
    this->connect(menuWidget->pushButton_optionsMenu, SIGNAL(clicked()), this, SLOT(on_pushButton_optionsMenu_clicked()));
    this->connect(menuWidget->pushButton_Highscore, SIGNAL(clicked()), this, SLOT(on_pushButton_Highscore_clicked()));
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
        QString buffer = controllField->getHighscore();
        buffer.replace(QString("#"), QString(" "));
        out << buffer;
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

void MainWindow::on_comboBox_PvPGamemode_activated(int index)
{
    gameMode = index;
}

void MainWindow::on_checkBox_OptionVollbild_clicked(bool checked)
{
    if (checked)
    {
        this->showFullScreen();
    }
    else {
        this->showNormal();
    }
}

void MainWindow::on_comboBox_PvCGamemode_activated(int index)
{
    gameMode = index;
}
