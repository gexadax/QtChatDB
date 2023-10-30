#ifndef SERVERFORM_H
#define SERVERFORM_H

#include "Database.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class ServerForm; }
QT_END_NAMESPACE

class ServerForm : public QDialog
{
    Q_OBJECT

public:
    ServerForm(QWidget *parent = nullptr);
    ~ServerForm();
    static int kInstanceCount;
    void updateChats();

private slots:
    void on_Choose_userButton_clicked();
    void on_BanButton_clicked();

private:
    Ui::ServerForm *ui;
};

#endif // SERVERFORM_H
