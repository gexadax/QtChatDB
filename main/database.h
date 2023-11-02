#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include "config.h"
#include <QMainWindow>
#include <QMessageBox>

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

void addChatMessage(std::string email,std::string message);
std::vector<std::string> getUserList();
void addPrivateMessage(std::string email,
                       std::string email_receiver,
                       std::string message);

#endif // DATABASE_H
