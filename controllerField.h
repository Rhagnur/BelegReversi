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

    //! Constructor
    controllerField();

    //! Deconstructor
    ~controllerField();

    /*!
     * \brief Switchs value between activePlayerand otherPlayer
     */
    void changeActivePlayer();

    /*!
     * \brief Saves new dictionary
     * \param newDict
     */
    void changeDict(std::string *newDict);

    /*!
     * \brief Checks for several win condition (win, draw)
     * \return bool
     * true if win or draw, else false
     */
    bool checkWin();

    /*!
     * \brief Calls the clearField method from viewField
     */
    void clearField();

    /*!
     * \brief Calculate and draw field
     * calculate the needed data for every single element of the field and calls the drawElement from viewField
     */
    void drawField();

    /*!
     * \brief Checks if click is valid
     * checks also if clicked field is possible turn
     * \param x
     * \param y
     * \return bool
     */
    bool evaluateClick(int x, int y);

    /*!
     * \brief Flips stones
     * starts at given field and looks for near stone which needs to be flipped
     * \param i
     * \param j
     */
    void flipStones(int i, int j);

    /*!
     * \brief Return highscore from database class
     * \return data
     */
    std::string getHighscore();

    /*!
     * \brief Return highscore by size from database class
     * \param size
     * \return data
     */
    std::string getHighscoreBySize(int size);

    /*!
     * \brief Return infoText
     * \return infoText
     */
    std::string getInfoText();

    /*!
     * \brief Return if user skipped a turn
     * \return skipped
     */
    bool getSkipped();

    /*!
     * \brief Pass by the viewField from viewField
     * \return viewField
     */
    viewField* getViewField();

    /*!
     * \brief Return value of an element from modelField
     * \param i
     * \param j
     * \return value
     */
    int getGamingFieldElementValue(int i, int j);

    /*!
     * \brief Return field height from modelField
     * \return fieldHeight
     */
    int getGamingFieldHeight();

    /*!
     * \brief Return field size from modelField
     * \return size
     */
    int getGamingFieldMatrixSize();

    /*!
     * \brief Return field width from modelField
     * \return
     */
    int getGamingFieldWidth();

    /*!
     * \brief Init the controllerField and doing presetting
     * \param fieldSize
     * \param design
     */
    void initControllerField(int fieldSize, int design);

    /*!
     * \brief Checks if field is possible turn
     * \param i
     * \param j
     * \return bool
     */
    bool isPossibleTurn(int i, int j);

    /*!
     * \brief Iterate through modelField to look for possible turn
     * \return bool
     */
    bool searchPossibleTurns();

    /*!
     * \brief Set new design as number
     * \param design
     */
    void setDesign(int design);

    /*!
     * \brief Set new fieldsize
     * \param w
     * \param h
     */
    void setFieldSize(int w, int h);

    /*!
     * \brief Set important Label and Textbox
     * Label, Textbox are given to controllerField so itself can add or change Text to the elements
     * \param infoBox
     * \param lcdPlayer1
     * \param lcdPlayer2
     */
    void setLabelAndLCD(QPlainTextEdit *infoBox, QLCDNumber *lcdPlayer1, QLCDNumber *lcdPlayer2);

    /*!
     * \brief Set new name for player1
     * \param name
     */
    void setPlayer1Name(std::string name);

    /*!
     * \brief Set new name for player2
     * \param name
     */
    void setPlayer2Name(std::string name);

    /*!
     * \brief Set bool variable showPossibleFields
     * If true then possible turns will be displayed
     * \param setting
     */
    void setShowPossTurns(bool setting);

    /*!
     * \brief Method for skipping a turn
     * Only possible if there is no possible turn left
     */
    void skipTurn();

    /*!
     * \brief Start new game
     */
    void startGame();

    /*!
     * \brief In- / Decrease stone count for players
     */
    void stoneCount();

    /*!
     * \brief Win condition for under pressure mode
     * If this method is called the time per turn for the activePlayer is zero, so otherPlayer wins automatically
     */
    void timeUpWin();

    /*!
     * \brief Simple turn in the game
     * Sets the field with the given coord to the value of the activePlayer
     * \param i
     * \param j
     */
    void turn(int i, int j);

private:

    SQLite *myDB = NULL;
    QPlainTextEdit *infoBox = NULL;
    QLCDNumber *lcdPlayer1 = NULL, *lcdPLayer2 = NULL;
    QSound *set1 = NULL, *set2 = NULL, *wrong = NULL, *applause = NULL, *applauseLight = NULL;

    std::string infoText, *myDict = NULL;
    bool skipped, showPossibleFields;
    int activePlayer, otherPlayer, design;

    viewField *viewGamingField = NULL;
    modelField *gamingField = NULL;
    modelPlayer *player[2];

};

#endif // CONTROLLERFIELD_H
