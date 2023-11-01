#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
//#include <QSqlDatabase>
//#include <QString>
#include "config.h"
//#include <memory>
#include <QMainWindow>
//#include <string>
//#include <vector>
#include <QMessageBox>
//#include <QWidget>

int addUser(std::string email);

class Database
{
public:
    Database();
    ~Database();

    bool openConnection();
    void closeConnection();
    bool createDatabase();
    bool createTable();
    int checkPassword(std::string email,std::string password);
    std::vector<std::string> getUserList();
    QString getid(QString Qemail);
    QString getQemail(QString Qid);

private:
    QSqlDatabase db;
    Config config;
};

#endif // DATABASE_H
