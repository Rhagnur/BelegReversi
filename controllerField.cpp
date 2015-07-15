#include "controllerField.h"
#include <iostream>
#include <ostream>
#include <istream>
#include <stdio.h>
#include <string>

controllerField::controllerField()
{
    viewGamingField = new viewField();
    isInit = false;
}

void controllerField::initControllerField(int fieldSize, int w, int h)
{
    skipped = false;
    isInit = true;
    player[0] = new modelPlayer("Jan", 0);
    player[1] = new modelPlayer("Baran", 0);
    activePlayer = 1;
    otherPlayer = 2;    
    gamingField = new modelField(fieldSize);
    gamingField->setFieldValue(gamingField->getFieldSize()/2 - 1,gamingField->getFieldSize()/2 - 1, activePlayer);
    gamingField->setFieldValue(gamingField->getFieldSize()/2,gamingField->getFieldSize()/2, activePlayer);
    gamingField->setFieldValue(gamingField->getFieldSize()/2,gamingField->getFieldSize()/2 - 1, otherPlayer);
    gamingField->setFieldValue(gamingField->getFieldSize()/2 - 1,gamingField->getFieldSize()/2, otherPlayer);
    player[0]->setPlayerStoneCount(2);
    player[1]->setPlayerStoneCount(2);
    infoText = player[activePlayer - 1]->getPlayerName() + " ist an der Reihe.";
    player1Text = player[0]->getPlayerName() + ": " + std::to_string(player[0]->getPlayerStoneCount());
    player2Text = player[1]->getPlayerName() + ": " + std::to_string(player[1]->getPlayerStoneCount());
    startGame();
    setFieldSize(w, h);
    drawField();
}

void controllerField::startGame()
{
        if (searchPossibleTurns())
        {
            std::cout<<"Mogliche Zuge gefunden"<<std::endl;
        }
        else
        {
            std::cout<<"Keine moglichen Zuge gefunden"<<std::endl;
        }

        gamingField->showFieldDebug();

}

void controllerField::turn(int i, int j)
{
    gamingField->setFieldValue(i, j , activePlayer);
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
    int temp = 0;
    if (w < h) {
        temp = w;
    }
    else {
        temp = h;
    }
    gamingField->setFieldWidth(temp);
    gamingField->setFieldHeight(temp);
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
            infoText = player[otherPlayer - 1]->getPlayerName() + " ist an der Reihe.";
            (turn(i, j));
            flipStones(i, j);
            player1Text = player[0]->getPlayerName() + ": " + std::to_string(player[0]->getPlayerStoneCount());
            player2Text = player[1]->getPlayerName() + ": " + std::to_string(player[1]->getPlayerStoneCount());
            changeActivePlayer();
            searchPossibleTurns();
            drawField();
            value = true;
            skipped = false;
        }
        else
        {
            //todo falscher zug
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
            infoText = player[0]->getPlayerName() + " hat gewonnen!";
            viewGamingField->clearField();
            viewGamingField->drawText(player[0]->getPlayerName() + " hat gewonnen!");
        }
        else if (player[0]->getPlayerStoneCount() < player[1]->getPlayerStoneCount())
        {
            infoText = player[1]->getPlayerName() + " hat gewonnen!";
            viewGamingField->clearField();
            viewGamingField->drawText(player[1]->getPlayerName() + " hat gewonnen!");
        }
        else
        {
            infoText = "Unentschieden!!!";
            viewGamingField->clearField();
            viewGamingField->drawText("Unentschieden!!!");
        }
    }
    else if (player[0]->getPlayerStoneCount() == 0)
    {
        infoText = player[1]->getPlayerName() + " hat gewonnen!";
        viewGamingField->clearField();
        viewGamingField->drawText(player[1]->getPlayerName() + " hat gewonnen!");
    }
    else if (player[1]->getPlayerStoneCount() == 0)
    {
        infoText = player[0]->getPlayerName() + " hat gewonnen!";
        viewGamingField->clearField();
        viewGamingField->drawText(player[0]->getPlayerName() + " hat gewonnen!");
    }
    else if (skipped) {
        if (player[0]->getPlayerStoneCount() > player[1]->getPlayerStoneCount())
        {
            infoText = player[0]->getPlayerName() + " hat gewonnen!";
            std::cout << infoText << std::endl;
            viewGamingField->clearField();
            viewGamingField->drawText(player[0]->getPlayerName() + " hat gewonnen!");
        }
        else if (player[1]->getPlayerStoneCount() > player[0]->getPlayerStoneCount())
        {
            infoText = player[1]->getPlayerName() + " hat gewonnen!";
            std::cout << infoText << std::endl;
            viewGamingField->clearField();
            viewGamingField->drawText(player[1]->getPlayerName() + " hat gewonnen!");
        }
        else
        {
            infoText = "Unentschieden!";
            std::cout << infoText << std::endl;
            viewGamingField->clearField();
            viewGamingField->drawText("Unentschieden!");
        }
    }
    else
    {
        //todo
    }
}

void controllerField::stoneCount()
{
    player[activePlayer - 1]->setPlayerStoneCount((player[activePlayer - 1]->getPlayerStoneCount()) + 1);
    player[otherPlayer - 1]->setPlayerStoneCount((player[otherPlayer - 1]->getPlayerStoneCount()) - 1);
}

viewField* controllerField::passViewField()
{
    return viewGamingField->getViewField();
}

void controllerField::drawField()
{

    for (int j = 0; j < gamingField->getFieldSize(); j++)
    {
        for (int i = 0; i < gamingField->getFieldSize(); i++)
        {

            int x = j*(gamingField->getFieldWidth()/gamingField->getFieldSize());
            int y = i*(gamingField->getFieldHeight()/gamingField->getFieldSize());
            int w = gamingField->getFieldWidth()/gamingField->getFieldSize();
            int h = gamingField->getFieldHeight()/gamingField->getFieldSize();

            viewGamingField->drawElement(x, y, w, h, gamingField->getFieldValue(i, j));
        }
    }
}

std::string controllerField::getInfoText()
{
    return infoText;
}

std::string controllerField::getPlayer1Text()
{
    return player1Text;
}

std::string controllerField::getPlayer2Text()
{
    return player2Text;
}

void controllerField::skipTurn()
{
    infoText = player[activePlayer - 1]->getPlayerName() + " konnte nicht ziehen. \n" + player[otherPlayer - 1]->getPlayerName() + " ist wieder dran. ";
    changeActivePlayer();
    searchPossibleTurns();
    drawField();
    skipped = true;
}

bool controllerField::getSkipped()
{
    return skipped;
}
