#include "controllerField.h"


controllerField::controllerField()
{
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

void controllerField::initControllerField(int fieldSize, int design)
{
    skipped = false;
    isInit = true;
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
    infoText = player[activePlayer - 1]->getPlayerName() + " " + myDict[8];
    infoBox->clear();
    infoBox->appendPlainText(QString::fromStdString(infoText));
}

void controllerField::startGame()
{
    searchPossibleTurns();
    gamingField->showFieldDebug();
}

void controllerField::timeUpWin()
{
    viewGamingField->clearField();
    viewGamingField->drawText(player[otherPlayer - 1]->getPlayerName() + + " " + myDict[6]);
}

void controllerField::turn(int i, int j)
{
    gamingField->setFieldValue(i, j , activePlayer);
    if (activePlayer == 1)
    {
        set1->play();
    }
    else
    {
        set2->play();
    }
    player[activePlayer - 1]->setPlayerStoneCount((player[activePlayer - 1]->getPlayerStoneCount()) + 1);
}

void controllerField::changeActivePlayer()
{
    int tmpPlayer = otherPlayer;
    otherPlayer = activePlayer;
    activePlayer = tmpPlayer;
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

void controllerField::setFieldSize(int w, int h)
{
    gamingField->setFieldWidth(w);
    gamingField->setFieldHeight(h);
}

void controllerField::clearField()
{
    viewGamingField->clearField();
}

int controllerField::getGamingFieldWidth()
{
    return gamingField->getFieldWidth();
}

int controllerField::getGamingFieldHeight()
{
    return gamingField->getFieldWidth();
}

int controllerField::getGamingFieldMatrixSize()
{
    return gamingField->getFieldSize();
}

int controllerField::getGamingFieldElementValue(int i, int j)
{
    return gamingField->getFieldValue(i, j);
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
            infoText = "\n" + player[otherPlayer - 1]->getPlayerName() + + " " + myDict[8];
            infoBox->clear();
            infoBox->appendPlainText(QString::fromStdString(infoText));
            (turn(i, j));
            flipStones(i, j);
            changeActivePlayer();
            searchPossibleTurns();
            value = true;
            skipped = false;
            viewGamingField->clear();
            drawField();


        }
        else
        {
            wrong->play();
        }
        checkWin();
    }
    return value;
}

void controllerField::checkWin()
{
    if (player[0]->getPlayerStoneCount() + player[1]->getPlayerStoneCount() == gamingField->getFieldSize() * gamingField->getFieldSize())
    {
        if (player[0]->getPlayerStoneCount() > player[1]->getPlayerStoneCount())
        {
            infoText = player[0]->getPlayerName() + + " " + myDict[6];
            viewGamingField->clearField();
            viewGamingField->drawText(player[0]->getPlayerName() + + " " + myDict[6]);
            myDB->insertPlayerHighscore(player[0]->getPlayerName(), player[0]->getPlayerStoneCount(), gamingField->getFieldSize());
            applause->play();
        }
        else if (player[0]->getPlayerStoneCount() < player[1]->getPlayerStoneCount())
        {
            infoText = player[1]->getPlayerName() + + " " + myDict[6];
            viewGamingField->clearField();
            viewGamingField->drawText(player[1]->getPlayerName() + + " " + myDict[6]);
            myDB->insertPlayerHighscore(player[1]->getPlayerName(), player[1]->getPlayerStoneCount(), gamingField->getFieldSize());
            applause->play();
        }
        else
        {
            infoText = myDict[25];
            viewGamingField->clearField();
            viewGamingField->drawText(myDict[25]);
            applauseLight->play();
        }
    }
    else if (player[0]->getPlayerStoneCount() == 0)
    {
        infoText = player[1]->getPlayerName() + + " " + myDict[6];
        viewGamingField->clearField();
        viewGamingField->drawText(player[1]->getPlayerName() + + " " + myDict[6]);
        myDB->insertPlayerHighscore(player[1]->getPlayerName(), player[1]->getPlayerStoneCount(), gamingField->getFieldSize());
        applause->play();
    }
    else if (player[1]->getPlayerStoneCount() == 0)
    {
        infoText = player[0]->getPlayerName() + + " " + myDict[6];
        viewGamingField->clearField();
        viewGamingField->drawText(player[0]->getPlayerName() + + " " + myDict[6]);
        myDB->insertPlayerHighscore(player[0]->getPlayerName(), player[0]->getPlayerStoneCount(), gamingField->getFieldSize());
        applause->play();
    }
    else if (skipped) {
        if (player[0]->getPlayerStoneCount() > player[1]->getPlayerStoneCount())
        {
            infoText = player[0]->getPlayerName() + + " " + myDict[6];
            std::cout << infoText << std::endl;
            viewGamingField->clearField();
            viewGamingField->drawText(player[0]->getPlayerName() + + " " + myDict[6]);
            myDB->insertPlayerHighscore(player[0]->getPlayerName(), player[0]->getPlayerStoneCount(), gamingField->getFieldSize());
            applause->play();
        }
        else if (player[1]->getPlayerStoneCount() > player[0]->getPlayerStoneCount())
        {
            infoText = player[1]->getPlayerName() + + " " + myDict[6];
            std::cout << infoText << std::endl;
            viewGamingField->clearField();
            viewGamingField->drawText(player[1]->getPlayerName() + + " " + myDict[6]);
            myDB->insertPlayerHighscore(player[1]->getPlayerName(), player[1]->getPlayerStoneCount(), gamingField->getFieldSize());
            applause->play();
        }
        else
        {
            infoText = myDict[25];
            std::cout << infoText << std::endl;
            viewGamingField->clearField();
            viewGamingField->drawText(myDict[25]);
            applauseLight->play();
        }
    }
}

void controllerField::stoneCount()
{
    player[activePlayer - 1]->setPlayerStoneCount((player[activePlayer - 1]->getPlayerStoneCount()) + 1);
    player[otherPlayer - 1]->setPlayerStoneCount((player[otherPlayer - 1]->getPlayerStoneCount()) - 1);

    lcdPlayer1->display(player[0]->getPlayerStoneCount());
    lcdPLayer2->display(player[1]->getPlayerStoneCount());
}

viewField* controllerField::passViewField()
{
    return viewGamingField->getViewField();
}

void controllerField::drawField()
{
    viewGamingField->clearField();
    std::cout << "Zeichne mit Design " + std::to_string(design) << std::endl;

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

std::string controllerField::getInfoText()
{
    return infoText;
}


void controllerField::skipTurn()
{
    infoText = player[activePlayer - 1]->getPlayerName() + " " + myDict[10] + "\n" + player[otherPlayer - 1]->getPlayerName() + " " + myDict[9];
    infoBox->clear();
    infoBox->appendPlainText(QString::fromStdString(infoText));
    changeActivePlayer();
    searchPossibleTurns();
    drawField();
    skipped = true;
}

bool controllerField::getSkipped()
{
    return skipped;
}

void controllerField::setDesign(int design)
{
    this->design = design;
    if (isInit)
    {
        drawField();
    }
}

void controllerField::setPlayer1Name(std::string name)
{
    player[0]->setPlayerName(name);
}

void controllerField::setPlayer2Name(std::string name)
{
    player[1]->setPlayerName(name);
}

void controllerField::setShowPossTurns(bool setting)
{
    showPossibleFields = setting;
}

std::string controllerField::getHighscore()
{
    return myDB->getHighscores();
}

std::string controllerField::getHighscoreBySize(int size)
{
    return myDB->getHighscoreBySize(size);
}

void controllerField::setLabelAndLCD(QPlainTextEdit *infoBox, QLCDNumber *lcdPlayer1, QLCDNumber *lcdPlayer2)
{
    this->infoBox = infoBox;
    this->lcdPlayer1 = lcdPlayer1;
    this->lcdPLayer2 = lcdPlayer2;
}

void controllerField::changeDict(std::string *newDict)
{
    myDict = newDict;
}
