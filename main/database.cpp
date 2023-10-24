#include "database.h"
#include <QSqlQuery>
#include <QFile>
#include <QSettings>

Database::Database()
{
    db = QSqlDatabase::addDatabase("QPSQL");
}

Database::~Database()
{
    closeConnection();
}

bool Database::openConnection()
{
    QMap<QString, QString> settings = config.readIniFile("config.ini");
    QString host = settings["HOSTNAME"];
    int port = settings["PORT"].toInt();
    QString databaseName = settings["DATABASENAME"];
    QString username = settings["USERNAME"];
    QString password = settings["PASSWORD"];

    db.setHostName(host);
    db.setPort(port);
    db.setDatabaseName(databaseName);
    db.setUserName(username);
    db.setPassword(password);

    if (db.open()) {
        return true;
    } else {

        return false;
    }
}

void Database::closeConnection()
{
    db.close();
}

bool Database::createDatabase()
{
    if (openConnection()) {
        QSqlQuery query;
        if (query.exec("CREATE DATABASE mydatabase")) {
            closeConnection();
            return true;
        }
        closeConnection();
    }
    return false;
}

bool Database::createTable()
{
    if (openConnection()) {
        QSqlQuery query;
        // if (query.exec("CREATE TABLE users (id serial primary key, name text)")) {
        //     closeConnection();
        //     return true;
        // }
        closeConnection();
    }
    return false;
}
