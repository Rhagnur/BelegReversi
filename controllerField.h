#ifndef CONTROLLERFIELD_H
#define CONTROLLERFIELD_H

#include "modelField.h"
#include "modelPlayer.h"
#include "viewField.h"

class controllerField
{
public:
    controllerField();
    void initControllerField(int fieldSize, int w, int h);
    bool searchPossibleTurns();
    bool isPossibleTurn(int i, int j);
    void flipStones(int i, int j);
    void changeActivePlayer();
    void startGame();
    void turn(int i, int j);
    void setFieldSize(int w, int h);
    int getGamingFieldWidth();
    int getGamingFieldHeight();
    int getGamingFieldMatrixSize();
    int getGamingFieldElementValue(int i, int j);
    bool evaluateClick(int x, int y);
    void checkWin();
    void stoneCount();
    viewField* passViewField();
    void drawField();
    std::string getInfoText();
    std::string getPlayer1Text();
    std::string getPlayer2Text();
    void skipTurn();
    bool isInit;


private:
    viewField *viewGamingField;
    modelField *gamingField;
    modelPlayer *player[2];
    int activePlayer, otherPlayer;
    std::string infoText, player1Text, player2Text;
};

#endif // CONTROLLERFIELD_H
