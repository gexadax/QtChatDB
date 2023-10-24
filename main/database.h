#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QSqlDatabase>
#include <QString>
#include "config.h"

class Database
{
public:
    Database();
    ~Database();

    bool openConnection();
    void closeConnection();
    bool createDatabase();
    bool createTable();

private:
    QSqlDatabase db;
    Config config;
};

#endif // DATABASE_H
