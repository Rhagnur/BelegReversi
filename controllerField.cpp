#include "controllerField.h"
#include <iostream>
#include <ostream>
#include <istream>
#include <stdio.h>

controllerField::controllerField(int fieldSize)
{
    activePlayer = 1;
    otherPlayer = 2;
    gamingField = new modelField(fieldSize);
    gamingField->setFieldValue(gamingField->getFieldSize()/2 - 1,gamingField->getFieldSize()/2 - 1, activePlayer);
    gamingField->setFieldValue(gamingField->getFieldSize()/2,gamingField->getFieldSize()/2, activePlayer);
    gamingField->setFieldValue(gamingField->getFieldSize()/2,gamingField->getFieldSize()/2 - 1, otherPlayer);
    gamingField->setFieldValue(gamingField->getFieldSize()/2 - 1,gamingField->getFieldSize()/2, otherPlayer);
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

        //schangeActivePlayer();

}

bool controllerField::turn(int i, int j)
{
    /* Check if player clicked on a field which is "possible" eg == 3 (all possible fields have been previously set to 3) */
    if (gamingField->getFieldValue(i, j) == 3)
    {
        gamingField->setFieldValue(i, j , activePlayer);
        //changeStones(i, j);

        //todo: Steine dazwischen umdrehen
        //todo: Playerwechsel

        return true;

    }
    else
    {
        //todo unmöglicher Zug...Sound und Ani
        return false;
    }
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
