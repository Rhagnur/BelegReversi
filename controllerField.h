#ifndef CONTROLLERFIELD_H
#define CONTROLLERFIELD_H

#include <QSound>
#include <QLabel>
#include <QLCDNumber>
#include <QPlainTextEdit>

#include <iostream>
#include <ostream>
#include <istream>
#include <stdio.h>
#include <string>

#include "modelField.h"
#include "modelPlayer.h"
#include "viewField.h"
#include "sqlite.h"



class controllerField
{
public:

    bool isInit;

    controllerField();
    ~controllerField();


    void changeActivePlayer();
    void changeDict(std::string *newDict);
    void checkWin();
    void clearField();
    void drawField();
    bool evaluateClick(int x, int y);
    void flipStones(int i, int j);
    std::string getHighscore();
    std::string getHighscoreBySize(int size);
    std::string getInfoText();
    bool getSkipped();
    viewField* getViewField();
    int getGamingFieldElementValue(int i, int j);
    int getGamingFieldHeight();
    int getGamingFieldMatrixSize();
    int getGamingFieldWidth();
    void initControllerField(int fieldSize, int design);
    bool isPossibleTurn(int i, int j);
    bool searchPossibleTurns();
    void setDesign(int design);
    void setFieldSize(int w, int h);
    void setLabelAndLCD(QPlainTextEdit *infoBox, QLCDNumber *lcdPlayer1, QLCDNumber *lcdPlayer2);
    void setPlayer1Name(std::string name);
    void setPlayer2Name(std::string name);
    void setShowPossTurns(bool setting);
    void skipTurn();
    void startGame();
    void stoneCount();
    void timeUpWin();
    void turn(int i, int j);

private:

    SQLite *myDB;
    QPlainTextEdit *infoBox;
    QLCDNumber *lcdPlayer1, *lcdPLayer2;
    QSound *set1, *set2, *wrong, *applause, *applauseLight;

    std::string infoText, *myDict;
    bool skipped, showPossibleFields;
    int activePlayer, otherPlayer, design;

    viewField *viewGamingField;
    modelField *gamingField;
    modelPlayer *player[2];

};

#endif // CONTROLLERFIELD_H
