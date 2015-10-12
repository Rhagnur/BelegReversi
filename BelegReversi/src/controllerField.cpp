#include "controllerField.h"


controllerField::controllerField()
{
    computer = new Ai();
    player[0] = new modelPlayer();
    player[1] = new modelPlayer();
    viewGamingField = new viewField();
    isInit = false;
    showPossibleFields = false;
    myDB = new SQLite();
    set1 = new QSound(":/music/blop.wav");
    set2 = new QSound(":/music/woosh.wav");
    wrong = new QSound(":/music/trombone.wav");
    applause = new QSound(":/music/applause.wav");
    applauseLight = new QSound(":/music/applauseLight.wav");
}

controllerField::controllerField(bool test)
{
    if (test)
    {
        player[0] = new modelPlayer();
        player[1] = new modelPlayer();
        viewGamingField = NULL;
        isInit = false;
        showPossibleFields = true;
        myDB = NULL;
        set1 = NULL;
        set2 = NULL;
        wrong = NULL;
        applause = NULL;
        applauseLight = NULL;
        testing = test;
    }
}

controllerField::~controllerField()
{
    delete computer;
    delete player[0];
    delete player[1];
    delete gamingField;
    delete viewGamingField;
    delete myDB;
    delete set1;
    delete set2;
    delete wrong;
    delete applause;
    delete applauseLight;
}

void controllerField::changeActivePlayer()
{
    int tmpPlayer = otherPlayer;
    otherPlayer = activePlayer;
    activePlayer = tmpPlayer;
}

void controllerField::changeDict(QString *newDict)
{
    myDict = newDict;
}

bool controllerField::checkWin()
{
    bool gameEnd = false;

    if (player[0]->getPlayerStoneCount() + player[1]->getPlayerStoneCount() == gamingField->getFieldSize() * gamingField->getFieldSize())
    {
        if (player[0]->getPlayerStoneCount() > player[1]->getPlayerStoneCount())
        {
            viewGamingField->clearField();
            viewGamingField->drawText(player[0]->getPlayerName() + " " + myDict[6]);
            myDB->insertPlayerHighscore(player[0]->getPlayerName(), player[0]->getPlayerStoneCount(), gamingField->getFieldSize());
            applause->play();
            gameEnd = true;
        }
        else if (player[0]->getPlayerStoneCount() < player[1]->getPlayerStoneCount())
        {
            viewGamingField->clearField();
            viewGamingField->drawText(player[1]->getPlayerName() + " " + myDict[6]);
            myDB->insertPlayerHighscore(player[1]->getPlayerName(), player[1]->getPlayerStoneCount(), gamingField->getFieldSize());
            applause->play();
            gameEnd = true;
        }
        else
        {
            viewGamingField->clearField();
            viewGamingField->drawText(myDict[25]);
            applauseLight->play();
            gameEnd = true;
        }
    }
    else if (player[0]->getPlayerStoneCount() == 0)
    {
        viewGamingField->clearField();
        viewGamingField->drawText(player[1]->getPlayerName() + + " " + myDict[6]);
        myDB->insertPlayerHighscore(player[1]->getPlayerName(), player[1]->getPlayerStoneCount(), gamingField->getFieldSize());
        applause->play();
        gameEnd = true;
    }
    else if (player[1]->getPlayerStoneCount() == 0)
    {
        viewGamingField->clearField();
        viewGamingField->drawText(player[0]->getPlayerName() + + " " + myDict[6]);
        myDB->insertPlayerHighscore(player[0]->getPlayerName(), player[0]->getPlayerStoneCount(), gamingField->getFieldSize());
        applause->play();
        gameEnd = true;
    }
    else if (skipped) {
        if (player[0]->getPlayerStoneCount() > player[1]->getPlayerStoneCount())
        {
            viewGamingField->clearField();
            viewGamingField->drawText(player[0]->getPlayerName() + + " " + myDict[6]);
            myDB->insertPlayerHighscore(player[0]->getPlayerName(), player[0]->getPlayerStoneCount(), gamingField->getFieldSize());
            applause->play();
            gameEnd = true;
        }
        else if (player[1]->getPlayerStoneCount() > player[0]->getPlayerStoneCount())
        {
            viewGamingField->clearField();
            viewGamingField->drawText(player[1]->getPlayerName() + + " " + myDict[6]);
            myDB->insertPlayerHighscore(player[1]->getPlayerName(), player[1]->getPlayerStoneCount(), gamingField->getFieldSize());
            applause->play();
            gameEnd = true;
        }
        else
        {
            viewGamingField->clearField();
            viewGamingField->drawText(myDict[25]);
            applauseLight->play();
            gameEnd = true;
        }
    }

    return gameEnd;
}

void controllerField::clearField()
{
    viewGamingField->clearField();
}

void controllerField::computerTurn()
{
    if (searchPossibleTurns())
    {
        std::vector<int> turnVector = computer->turn(gamingField, activePlayer, otherPlayer, difficulty);

        if (turnVector.empty())
        {
            if (!checkWin())
            {
                skipTurn();
            }
        }
        else
        {
            int i = turnVector.at(0);
            int j = turnVector.at(1);
            //std::cout << "Zug ist i: " + std::to_string(i) + " j: " + std::to_string(j) << std::endl;
            infoBox->clear();
            infoBox->appendPlainText(player[otherPlayer - 1]->getPlayerName() + " " + myDict[8]);
            turn(i, j);
            flipStones(i, j);
            changeActivePlayer();
            searchPossibleTurns();
            skipped = false;
            viewGamingField->clear();
            drawField();
        }
    }
    else {
        std::cout << "Nix gefunden ... :(" << std::endl;
        if (!checkWin())
        {
            skipTurn();
        }
    }

}

void controllerField::drawField()
{
    viewGamingField->clearField();

    for (int j = 0; j < gamingField->getFieldSize(); j++)
    {
        for (int i = 0; i < gamingField->getFieldSize(); i++)
        {

            int x = j*(gamingField->getFieldWidth()/gamingField->getFieldSize());
            int y = i*(gamingField->getFieldHeight()/gamingField->getFieldSize());
            int w = gamingField->getFieldWidth()/gamingField->getFieldSize();
            int h = gamingField->getFieldHeight()/gamingField->getFieldSize();

            viewGamingField->drawElement(x, y, w, h, gamingField->getFieldValue(i, j), design, showPossibleFields);
        }
    }
}

bool controllerField::evaluateClick(int x, int y)
{
    bool value = false;
    if (x > 0 && x < gamingField->getFieldWidth() && y > 0 && y < gamingField->getFieldHeight())
    {
        int i = y / (gamingField->getFieldHeight()/gamingField->getFieldSize());
        int j = x / (gamingField->getFieldWidth()/gamingField->getFieldSize());

        if (gamingField->getFieldValue(i, j) == 3)
        {
            infoBox->clear();
            infoBox->appendPlainText(player[otherPlayer - 1]->getPlayerName() + " " + myDict[8]);
            turn(i, j);
            flipStones(i, j);
            changeActivePlayer();
            searchPossibleTurns();
            value = true;
            skipped = false;
            viewGamingField->clear();
            drawField();

            if(isAiGame) {
                computerTurn();
            }

        }
        else
        {
            wrong->play();
        }
    }
    return value;
}

void controllerField::flipStones(int i, int j)
{
    //flip down
    if (i != gamingField->getFieldSize() - 1 && gamingField->getFieldValue(i + 1, j) == otherPlayer)
    {
        int iIterator = i + 1;
        while (iIterator < gamingField->getFieldSize() - 1 && gamingField->getFieldValue(iIterator, j) == otherPlayer)
        {
            iIterator++;
        }
        if (gamingField->getFieldValue(iIterator, j) == activePlayer)
        {
            for (int y = i + 1; y < iIterator; y++)
            {
                gamingField->setFieldValue(y, j, activePlayer);
                stoneCount();
            }
        }
    }
    //flip down-right
    if (i != gamingField->getFieldSize() - 1 && j != gamingField->getFieldSize() - 1 && gamingField->getFieldValue(i + 1, j + 1) == otherPlayer)
    {
        int iIterator = i + 1;
        int jIterator = j + 1;
        while (iIterator < gamingField->getFieldSize() - 1 && jIterator < gamingField->getFieldSize() - 1 && gamingField->getFieldValue(iIterator, jIterator) == otherPlayer)
        {
            iIterator++;
            jIterator++;
        }
        if (gamingField->getFieldValue(iIterator, jIterator) == activePlayer)
        {
            int y = i + 1;
            int x = j + 1;
            while (y < iIterator && x < jIterator)
            {
                gamingField->setFieldValue(y, x, activePlayer);
                stoneCount();
                y++;
                x++;
            }
        }
    }
    //flip right
    if (i != gamingField->getFieldSize() - 1 && j != gamingField->getFieldSize() - 1 && gamingField->getFieldValue(i, j + 1) == otherPlayer)
    {
        int jIterator = j + 1;
        while (jIterator < gamingField->getFieldSize() - 1 && gamingField->getFieldValue(i, jIterator) == otherPlayer)
        {
            jIterator++;
        }
        if (gamingField->getFieldValue(i, jIterator) == activePlayer)
        {
            for (int x = j + 1; x < jIterator; x++)
            {
                gamingField->setFieldValue(i, x, activePlayer);
                stoneCount();
            }
        }
    }
    //flip up-right
    if (i != 0 && j != gamingField->getFieldSize() - 1 && gamingField->getFieldValue(i - 1, j + 1) == otherPlayer)
    {
        int iIterator = i - 1;
        int jIterator = j + 1;
        while (iIterator > 0 && jIterator < gamingField->getFieldSize() - 1 && gamingField->getFieldValue(iIterator, jIterator) == otherPlayer)
        {
            iIterator--;
            jIterator++;
        }
        if (gamingField->getFieldValue(iIterator, jIterator) == activePlayer)
        {
            int y = i - 1;
            int x = j + 1;
            while (y > iIterator && x < jIterator)
            {
                gamingField->setFieldValue(y, x, activePlayer);
                stoneCount();
                y--;
                x++;
            }
        }
    }
    //flip up
    if (i != 0 && gamingField->getFieldValue(i - 1, j) == otherPlayer)
    {
        int iIterator = i - 1;
        while (iIterator > 0 && gamingField->getFieldValue(iIterator, j) == otherPlayer)
        {
            iIterator--;
        }
        if (gamingField->getFieldValue(iIterator, j) == activePlayer)
        {
            for (int y = i - 1; y > iIterator; y--)
            {
                gamingField->setFieldValue(y, j, activePlayer);
                stoneCount();
            }
        }
    }
    //flip up-left
    if (i != 0 && j != 0 && gamingField->getFieldValue(i - 1, j - 1) == otherPlayer)
    {
        int iIterator = i - 1;
        int jIterator = j - 1;
        while (iIterator > 0 && jIterator > 0 && gamingField->getFieldValue(iIterator, jIterator) == otherPlayer)
        {
            iIterator--;
            jIterator--;
        }
        if (gamingField->getFieldValue(iIterator, jIterator) == activePlayer)
        {
            int y = i - 1;
            int x = j - 1;
            while (y > iIterator && x > jIterator)
            {
                gamingField->setFieldValue(y, x, activePlayer);
                stoneCount();
                y--;
                x--;
            }
        }
    }
    //flip left
    if (j != 0 && gamingField->getFieldValue(i, j - 1) == otherPlayer)
    {
        int jIterator = j - 1;
        while (jIterator > 0 && gamingField->getFieldValue(i, jIterator) == otherPlayer)
        {
            jIterator--;
        }
        if (gamingField->getFieldValue(i, jIterator) == activePlayer)
        {
            for (int x = j - 1; x > jIterator; x--)
            {
                gamingField->setFieldValue(i, x, activePlayer);
                stoneCount();
            }
        }
    }
    //flip down-left
    if (i != gamingField->getFieldSize() - 1 && j != 0 && gamingField->getFieldValue(i + 1, j - 1) == otherPlayer)
    {
        int iIterator = i + 1;
        int jIterator = j - 1;
        while (iIterator < gamingField->getFieldSize() - 1 && jIterator > 0 && gamingField->getFieldValue(iIterator, jIterator) == otherPlayer)
        {
            iIterator++;
            jIterator--;
        }
        if (gamingField->getFieldValue(iIterator, jIterator) == activePlayer)
        {
            int y = i + 1;
            int x = j - 1;
            while (y < iIterator && x > jIterator)
            {
                gamingField->setFieldValue(y, x, activePlayer);
                stoneCount();
                y++;
                x--;
            }
        }
    }
}

modelField* controllerField::getField()
{
    return gamingField;
}

QString controllerField::getHighscore()
{
    return myDB->getHighscores();
}

QString controllerField::getHighscoreBySize(int size)
{
    return myDB->getHighscoreBySize(size);
}

bool controllerField::getSkipped()
{
    return skipped;
}

viewField* controllerField::getViewField()
{
    return viewGamingField->getViewField();
}

int controllerField::getGamingFieldElementValue(int i, int j)
{
    return gamingField->getFieldValue(i, j);
}

int controllerField::getGamingFieldHeight()
{
    return gamingField->getFieldWidth();
}

int controllerField::getGamingFieldMatrixSize()
{
    return gamingField->getFieldSize();
}

int controllerField::getGamingFieldWidth()
{
    return gamingField->getFieldWidth();
}

void controllerField::initControllerField(int fieldSize, int design)
{
    skipped = false;
    isInit = true;
    isAiGame = false;
    activePlayer = 1;
    otherPlayer = 2;
    this->design = design;
    gamingField = new modelField(fieldSize);
    gamingField->setFieldValue(gamingField->getFieldSize()/2 - 1,gamingField->getFieldSize()/2 - 1, activePlayer);
    gamingField->setFieldValue(gamingField->getFieldSize()/2,gamingField->getFieldSize()/2, activePlayer);
    gamingField->setFieldValue(gamingField->getFieldSize()/2,gamingField->getFieldSize()/2 - 1, otherPlayer);
    gamingField->setFieldValue(gamingField->getFieldSize()/2 - 1,gamingField->getFieldSize()/2, otherPlayer);
    player[0]->setPlayerStoneCount(2);
    player[1]->setPlayerStoneCount(2);
    infoBox->clear();
    infoBox->appendPlainText(player[activePlayer - 1]->getPlayerName() + " " + myDict[8]);

}

void controllerField::initControllerFieldForTest(int size)
{
    skipped = false;
    isInit = true;
    activePlayer = 1;
    otherPlayer = 2;
    player[0]->setPlayerName(QString("TestplayerOne"));
    player[1]->setPlayerName(QString("TestplayerTwo"));
    gamingField = new modelField(size);
    gamingField->setFieldValue(gamingField->getFieldSize()/2 - 1,gamingField->getFieldSize()/2 - 1, activePlayer);
    gamingField->setFieldValue(gamingField->getFieldSize()/2,gamingField->getFieldSize()/2, activePlayer);
    gamingField->setFieldValue(gamingField->getFieldSize()/2,gamingField->getFieldSize()/2 - 1, otherPlayer);
    gamingField->setFieldValue(gamingField->getFieldSize()/2 - 1,gamingField->getFieldSize()/2, otherPlayer);
    player[0]->setPlayerStoneCount(2);
    player[1]->setPlayerStoneCount(2);
}

bool controllerField::isPossibleTurn(int i, int j)
{
            if (i != gamingField->getFieldSize() - 1 && gamingField->getFieldValue(i + 1, j) == otherPlayer)
            {
                int iIterator = i + 1;
                while (iIterator < gamingField->getFieldSize() - 1 && gamingField->getFieldValue(iIterator, j) == otherPlayer)
                {
                    iIterator++;
                }
                if (gamingField->getFieldValue(iIterator, j) == activePlayer) return true;
            }
            if (i != gamingField->getFieldSize() - 1 && j != gamingField->getFieldSize() - 1 && gamingField->getFieldValue(i + 1, j + 1) == otherPlayer)
            {
                int iIterator = i + 1;
                int jIterator = j + 1;
                while (iIterator < gamingField->getFieldSize() - 1 && jIterator < gamingField->getFieldSize() - 1 && gamingField->getFieldValue(iIterator, jIterator) == otherPlayer)
                {
                    iIterator++;
                    jIterator++;
                }
                if (gamingField->getFieldValue(iIterator, jIterator) == activePlayer) return true;
            }
            if (i != gamingField->getFieldSize() - 1 && j != gamingField->getFieldSize() - 1 && gamingField->getFieldValue(i, j + 1) == otherPlayer)
            {
                int jIterator = j + 1;
                while (jIterator < gamingField->getFieldSize() - 1 && gamingField->getFieldValue(i, jIterator) == otherPlayer)
                {
                    jIterator++;
                }
                if (gamingField->getFieldValue(i, jIterator) == activePlayer) return true;
            }
            if (i != 0 && j != gamingField->getFieldSize() - 1 && gamingField->getFieldValue(i - 1, j + 1) == otherPlayer)
            {
                int iIterator = i - 1;
                int jIterator = j + 1;
                while (iIterator > 0 && jIterator < gamingField->getFieldSize() - 1 && gamingField->getFieldValue(iIterator, jIterator) == otherPlayer)
                {
                    iIterator--;
                    jIterator++;
                }
                if (gamingField->getFieldValue(iIterator, jIterator) == activePlayer) return true;
            }
            if (i != 0 && gamingField->getFieldValue(i - 1, j) == otherPlayer)
            {
                int iIterator = i - 1;
                while (iIterator > 0 && gamingField->getFieldValue(iIterator, j) == otherPlayer)
                {
                    iIterator--;
                }
                if (gamingField->getFieldValue(iIterator, j) == activePlayer) return true;
            }
            if (i != 0 && j != 0 && gamingField->getFieldValue(i - 1, j - 1) == otherPlayer)
            {
                int iIterator = i - 1;
                int jIterator = j - 1;
                while (iIterator > 0 && jIterator > 0 && gamingField->getFieldValue(iIterator, jIterator) == otherPlayer)
                {
                    iIterator--;
                    jIterator--;
                }
                if (gamingField->getFieldValue(iIterator, jIterator) == activePlayer) return true;
            }
            if (j != 0 && gamingField->getFieldValue(i, j - 1) == otherPlayer)
            {
                int jIterator = j - 1;
                while (jIterator > 0 && gamingField->getFieldValue(i, jIterator) == otherPlayer)
                {
                     jIterator--;
                }
                if (gamingField->getFieldValue(i, jIterator) == activePlayer) return true;
            }
            if (i != gamingField->getFieldSize() - 1 && j != 0 && gamingField->getFieldValue(i + 1, j - 1) == otherPlayer)
            {
                int iIterator = i + 1;
                int jIterator = j - 1;
                while (iIterator < gamingField->getFieldSize() - 1 && jIterator > 0 && gamingField->getFieldValue(iIterator, jIterator) == otherPlayer)
                {
                    iIterator++;
                    jIterator--;
                }
                if (gamingField->getFieldValue(iIterator, jIterator) == activePlayer) return true;
            }
            return false;
}

bool controllerField::searchPossibleTurns()
{
    bool foundPossibleTurn = false;

    for (int i = 0; i < gamingField->getFieldSize(); i++)
    {
        for (int j = 0; j < gamingField->getFieldSize(); j++)
        {
            /* First, set all previous possible fields back to normal */
            if (gamingField->getFieldValue(i, j) == 3)
            {
                gamingField->setFieldValue(i, j , 0);
            }
            /* Now, check which fields are possible turns */
            if (gamingField->getFieldValue(i, j) == 0)
            {
                if (isPossibleTurn(i, j))
                {
                    gamingField->setFieldValue(i, j, 3);
                    foundPossibleTurn = true;
                }
            }
        }
    }
    return foundPossibleTurn;
}

void controllerField::setAiGame(bool isAiGame, bool isAiFirst)
{
    this->isAiGame = isAiGame;
    aiFirst = isAiFirst;
}

void controllerField::setDesign(int design)
{
    this->design = design;
    if (isInit)
    {
        drawField();
    }
}

void controllerField::setDifficulty(QString difficulty)
{
    this->difficulty = difficulty;
}

void controllerField::setFieldSize(int w, int h)
{
    gamingField->setFieldWidth(w);
    gamingField->setFieldHeight(h);
}

void controllerField::setLabelAndLCD(QPlainTextEdit *infoBox, QLCDNumber *lcdPlayer1, QLCDNumber *lcdPlayer2)
{
    this->infoBox = infoBox;
    this->lcdPlayer1 = lcdPlayer1;
    this->lcdPLayer2 = lcdPlayer2;
}

void controllerField::setPlayer1Name(QString name)
{
    player[0]->setPlayerName(name);
}

void controllerField::setPlayer2Name(QString name)
{
    player[1]->setPlayerName(name);
}

void controllerField::setShowPossTurns(bool setting)
{
    showPossibleFields = setting;
}

void controllerField::skipTurn()
{
    infoBox->clear();
    infoBox->appendPlainText(player[activePlayer - 1]->getPlayerName() + " " + myDict[10] + "\n" + player[otherPlayer - 1]->getPlayerName() + " " + myDict[9]);
    changeActivePlayer();
    searchPossibleTurns();
    drawField();
    skipped = true;
    if(isAiGame) {
        computerTurn();
    }
}

void controllerField::startGame()
{
    searchPossibleTurns();
    if (aiFirst) {
        drawField();
        computerTurn();
    }
}

void controllerField::stoneCount()
{
    player[activePlayer - 1]->setPlayerStoneCount((player[activePlayer - 1]->getPlayerStoneCount()) + 1);
    player[otherPlayer - 1]->setPlayerStoneCount((player[otherPlayer - 1]->getPlayerStoneCount()) - 1);

    if(!testing)
    {
        lcdPlayer1->display(player[0]->getPlayerStoneCount());
        lcdPLayer2->display(player[1]->getPlayerStoneCount());
    }

}

void controllerField::timeUpWin()
{
    viewGamingField->clearField();
    viewGamingField->drawText(player[otherPlayer - 1]->getPlayerName() + + " " + myDict[6]);
    applauseLight->play();
}

void controllerField::turn(int i, int j)
{
    gamingField->setFieldValue(i, j , activePlayer);
    if (activePlayer == 1 && set1)
    {
        set1->play();
    }
    if (activePlayer == 2 && set2)
    {
        set2->play();
    }
    player[activePlayer - 1]->setPlayerStoneCount((player[activePlayer - 1]->getPlayerStoneCount()) + 1);
}



















