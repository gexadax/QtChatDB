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
        if (createDatabase()) {
            return db.open();
        } else {
            qDebug() << "Failed to create database.";
            return false;
        }
    }
}

void Database::closeConnection()
{
    db.close();
}

bool Database::createDatabase()
{
    QMap<QString, QString> settings = config.readIniFile("server.ini");
    QString host = settings["HOSTNAME"];
    QString databaseName = settings["DATABASENAME"];
    QString username = settings["USERNAME"];
    QString password = settings["PASSWORD"];

    qDebug() << "Read HOSTNAME from server.ini: " << host;
    qDebug() << "Read DATABASENAME from server.ini: " << databaseName;
    qDebug() << "Read USERNAME from server.ini: " << username;

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(host);
    db.setDatabaseName("postgres");
    db.setUserName(username);
    db.setPassword(password);

    if (db.open()) {
        QSqlQuery query;
        QString createDbQuery = QString("CREATE DATABASE %1").arg(databaseName);

        qDebug() << "Create DB query: " << createDbQuery;

        if (query.exec(createDbQuery)) {
            qDebug() << "Database created successfully";
            return true;
        } else {
            qDebug() << "Error creating database:" << query.lastError().text();
        }

        db.close();
    } else {
        qDebug() << "Failed to open a connection to PostgreSQL: " << db.lastError().text();
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
