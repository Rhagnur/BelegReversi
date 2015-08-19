#ifndef SQLITE_H
#define SQLITE_H

#include <iostream>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

class SQLite
{
public:
    SQLite();
    ~SQLite();
    void insertPlayerHighscore(std::string playerName, int stoneCount, int fieldSize);
    std::string getHighscores();

private:
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");
    void writePlaceholder();
    void deleteAllData();

};

#endif // SQLITE_H
