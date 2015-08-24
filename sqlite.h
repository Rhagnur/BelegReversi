#ifndef SQLITE_H
#define SQLITE_H

#include <iostream>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

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

    //! Insert method
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

    //! Get method
    /*!
     * \brief Gets the highscore data
     * Highscore data format is (name - score - fieldsize), returns only the 12 best player sort by score
     * \return highscoreString
     * complete data as string, lines seperated with '\n’
     */
    std::string getHighscores();

    //! Get method
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
    void writePlaceholder();
    void deleteAllData();

};

#endif // SQLITE_H
