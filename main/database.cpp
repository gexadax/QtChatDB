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
    QMap<QString, QString> settings = config.readIniFile("server.ini");
    QString host = settings["HOSTNAME"];
    QString databaseName = settings["DATABASENAME"];
    QString username = settings["USERNAME"];
    QString password = settings["PASSWORD"];

    db.setHostName(host);
    db.setDatabaseName(databaseName);
    db.setUserName(username);
    db.setPassword(password);

    if (db.open()) {
        qDebug() << "Database connection opened successfully";
        return true;
    } else {
        qDebug() << "Failed to open database connection. Error: " << db.lastError().text();
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
        if (query.exec("CREATE DATABASE chatdb")) {
            qDebug() << "Database created successfully";
            closeConnection();
            return true;
        } else {
            qDebug() << "Error creating database:" << query.lastError().text();
            closeConnection();
        }
    } else {
        qDebug() << "Error opening connection to the database";
    }
    return false;
}

bool Database::createTable()
{
    if (openConnection()) {
        QSqlQuery query;
         if (query.exec("CREATE TABLE users (id serial primary key, name text)")) {
             closeConnection();
             return true;
         }
        closeConnection();
    }
    return false;
}
