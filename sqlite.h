#ifndef SQLITE_H
#define SQLITE_H

#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

#include <iostream>

//! Database class
/*!
 * \brief Class for creating and getting access to SQLite database
 */
class SQLite
{
public:
    //! Constructor
    SQLite();

    //! Deconstructor
    ~SQLite();

    /*!
     * \brief Insert new data in db
     * \param playerName
     * Name of the Player
     * \param stoneCount
     * Stonecount of the player
     * \param fieldSize
     * Size of the gamingfield
     */
    void insertPlayerHighscore(std::string playerName, int stoneCount, int fieldSize);

    /*!
     * \brief Gets the highscore data
     * Highscore data format is (name - score - fieldsize), returns only the 12 best player sort by score
     * \return highscoreString
     * complete data as string, lines seperated with '\n’
     */
    std::string getHighscores();

    /*!
     * \brief Gets the highscore data
     * Highscore data format is (name - score), returns only the 12 best player sort by score for the choosen fiedsize
     * \param size
     * Choosen fieldsize
     * \return highscoreString
     * complete data as string, lines seperated with '\n’
     */
    std::string getHighscoreBySize(int size);

private:

    QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");

    //Nur für Debugzwecke
    void writePlaceholder();
    void deleteAllData();

};

#endif // SQLITE_H
