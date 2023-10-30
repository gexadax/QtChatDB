#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QSqlDatabase>
#include <QString>
#include "config.h"
#include <memory>
#include <QMainWindow>
#include <string>
#include <vector>
#include <QMessageBox>
#include <QWidget>

class Database
{
public:
    Database();
    ~Database();

    bool openConnection();
    void closeConnection();
    bool createDatabase();
    bool createTable();

    std::vector<std::string> getUserList();
    QString getid(QString Qemail);
    QString getQemail(QString Qid);

private:
    QSqlDatabase db;
    Config config;
};

#endif // DATABASE_H
