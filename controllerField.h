#ifndef CONTROLLERFIELD_H
#define CONTROLLERFIELD_H

#include "modelField.h"
#include "modelPlayer.h"
#include "viewField.h"
#include "sqlite.h"
#include <QSound>
#include <QLabel>
#include <QLCDNumber>
#include <QPlainTextEdit>

class controllerField
{
public:
    controllerField();
    void initControllerField(int fieldSize, int design);
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
    std::string getHighscore();
    std::string getHighscoreBySize(int size);
    bool evaluateClick(int x, int y);
    void checkWin();
    void stoneCount();
    viewField* passViewField();
    void drawField();
    std::string getInfoText();
    void setPlayer1Name(std::string name);
    void setPlayer2Name(std::string name);
    void setShowPossTurns(bool setting);
    void skipTurn();
    bool isInit;
    void clearField();
    bool getSkipped();
    void setDesign(int design);
    void setLabelAndLCD(QPlainTextEdit *infoBox, QLCDNumber *lcdPlayer1, QLCDNumber *lcdPlayer2);


private:
    viewField *viewGamingField;
    modelField *gamingField;
    modelPlayer *player[2];
    SQLite *myDB;
    int activePlayer, otherPlayer, design;
    std::string infoText;
    bool skipped, showPossibleFields;
    QSound *set1, *set2, *wrong, *applause, *applauseLight;
    QPlainTextEdit *infoBox;
    QLCDNumber *lcdPlayer1, *lcdPLayer2;
};

#endif // CONTROLLERFIELD_H
