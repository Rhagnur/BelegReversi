#ifndef CONTROLLERFIELD_H
#define CONTROLLERFIELD_H

#include "modelField.h"
#include "modelPlayer.h"

class controllerField
{
public:
    controllerField(int fieldSize);
    bool searchPossibleTurns();
    bool isPossibleTurn(int i, int j);
    void flipStones(int i, int j);
    void changeActivePlayer();
    void startGame();
    void turn(int i, int j);
    void startDrawing();
    void setFieldSize(int w, int h);
    int getGamingFieldWidth();
    int getGamingFieldHeight();
    int getGamingFieldMatrixSize();
    int getGamingFieldElementValue(int i, int j);
    bool evaluateClick(int x, int y);
    bool checkWin();
    void stoneCount(int color);


private:
    modelField* gamingField;
    modelPlayer* player[2];
    int activePlayer, otherPlayer;
};

#endif // CONTROLLERFIELD_H
