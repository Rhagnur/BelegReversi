#include "sqlite.h"

SQLite::SQLite()
{
    if (!QDir("db").exists())
    {
        std::cout << "[INFO] Create new db dir 'db/'" << std::endl;
        QDir().mkdir("db");
    }
    myDB.setDatabaseName("db/database.db");
    myDB.open();
    myDB.exec("CREATE TABLE highscore(id INTEGER  PRIMARY KEY NOT NULL,name CHAR(20) NOT NULL,score INTEGER NOT NULL, fieldsize INTEGER NOT NULL);");
}
SQLite::~SQLite()
{
    myDB.close();
}

std::string SQLite::getHighscores()
{
    std::string buffer = "";
    QSqlQuery query;
    std::cout << "[INFO] Query to db" << std::endl;
    query.exec("SELECT name, score, fieldsize FROM highscore ORDER BY score DESC LIMIT 12;");


    while (query.next()) {
        QString name = query.value(0).toString();
        int score = query.value(1).toInt();
        int fieldsize = query.value(2).toInt();
        std::string nameBuffer = name.toStdString();
        buffer += nameBuffer + "#" + std::to_string(score) + "#" + std::to_string(fieldsize) + "\n";
    }

    return buffer;
}

std::string SQLite::getHighscoreBySize(int size)
{
    std::string buffer = "";
    QSqlQuery query;
    std::cout << "[INFO] Query to db" << std::endl;
    QString queryString = "SELECT name, score FROM highscore WHERE fieldsize = " + QString::fromStdString(std::to_string(size)) + " ORDER BY score DESC LIMIT 12 ;";
    query.exec(queryString);


    while (query.next()) {
        QString name = query.value(0).toString();
        int score = query.value(1).toInt();
        std::string nameBuffer = name.toStdString();
        buffer += nameBuffer + "#" + std::to_string(score) + "\n";
    }

    return buffer;
}

void SQLite::insertPlayerHighscore(std::string playerName, int stoneCount, int fieldSize)
{
    QSqlQuery query;
    QString queryMessage = "";
    std::string buffer = "";
    int id = 0;

    query.exec("SELECT MAX(id) FROM highscore;");
    while (query.next()) {
        id = query.value(0).toInt() + 1;
    }

    buffer = "INSERT INTO highscore (id, name, score, fieldsize) VALUES (" + std::to_string(id) + ",'" + playerName + "'," + std::to_string(stoneCount) + "," + std::to_string(fieldSize) + ");";
    queryMessage = QString::fromStdString(buffer);

    std::cout << "[INFO] Add new player score to db" << std::endl;
    myDB.exec(queryMessage);
}

void SQLite::writePlaceholder()
{
    myDB.exec("INSERT INTO highscore(id,name,score, fieldsize) VALUES (1,'Jan', 1, 1);");
}

void SQLite::deleteAllData()
{
    myDB.exec("DELETE FROM highscore");
}
