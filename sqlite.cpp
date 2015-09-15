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

QString SQLite::getHighscores()
{
    QString buffer = "";
    QSqlQuery query;
    std::cout << "[INFO] Query to db" << std::endl;
    query.exec("SELECT name, score, fieldsize FROM highscore ORDER BY score DESC LIMIT 12;");


    while (query.next()) {
        QString name = query.value(0).toString();
        int score = query.value(1).toInt();
        int fieldsize = query.value(2).toInt();

        buffer += name + "#" + QString::number(score) + "#" + QString::number(fieldsize) + "\n";
    }

    return buffer;
}

QString SQLite::getHighscoreBySize(int size)
{
    QString buffer = "";
    QSqlQuery query;
    std::cout << "[INFO] Query to db" << std::endl;
    QString queryString = "SELECT name, score FROM highscore WHERE fieldsize = " + QString::number(size) + " ORDER BY score DESC LIMIT 12 ;";
    query.exec(queryString);


    while (query.next()) {
        QString name = query.value(0).toString();
        int score = query.value(1).toInt();
        buffer += name + "#" + QString::number(score) + "\n";
    }

    return buffer;
}

void SQLite::insertPlayerHighscore(QString playerName, int stoneCount, int fieldSize)
{
    QSqlQuery query;
    QString queryMessage = "";
    int id = 0;

    query.exec("SELECT MAX(id) FROM highscore;");
    while (query.next()) {
        id = query.value(0).toInt() + 1;
    }

    queryMessage = "INSERT INTO highscore (id, name, score, fieldsize) VALUES (" + QString::number(id) + ",'" + playerName + "'," + QString::number(stoneCount) + "," + QString::number(fieldSize) + ");";

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
