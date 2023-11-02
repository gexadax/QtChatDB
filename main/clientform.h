#ifndef CLIENTFORM_H
#define CLIENTFORM_H

#include <QMainWindow>
#include <memory>
#include "Database.h"

namespace Ui {
class ClientForm;
}

class ClientForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientForm(int userId,QString Qemail,QWidget *parent = nullptr);
    ~ClientForm();
    static ClientForm* createClient();
    static int kInstanceCount;

private slots:

    void on_messageLineEdit_returnPressed();
    void on_sendMessageButton_clicked();
    void on_privateMessageButton_clicked();
    void on_actionOpen_another_client_triggered();
    void on_actionCloseThisClient_triggered();
    void updateChats();

private:
    Ui::ClientForm *ui;
    int m_userId;
    QString m_Qemail;
};

#endif // CLIENTFORM_H
