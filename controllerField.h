#ifndef CONTROLLERFIELD_H
#define CONTROLLERFIELD_H

#include "modelField.h"

class controllerField
{
public:
    controllerField(int fieldSize);
    bool searchPossibleTurns();
    bool isPossibleTurn(int i, int j);
    void changeActivePlayer();
    void startGame();
    bool turn(int i, int j);

private:
    modelField* gamingField;
    int activePlayer, otherPlayer;
};

#endif // CONTROLLERFIELD_H
