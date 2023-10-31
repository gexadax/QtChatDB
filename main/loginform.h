#ifndef LOGINFORM_H
#define LOGINFORM_H

#include "database.h"
#include <QFormLayout>

#include <QWidget>
#include <memory>

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();
    QFormLayout* getFormLayoutLogin();
    void PasswordEdit();
    void checkPassword();

signals:
    void RegistrationRequested();
    void accepted(int userId,QString Qemail);
    void rejected();
private slots:
    void on_pushButtonRegister_clicked();
    void on_pushButtonOk_clicked();
    void on_pushButtonCancel_clicked();

    void on_pushButtonRegistrationCancel_clicked();

    void on_pushButtonRegistrationOk_clicked();

private:
    Ui::LoginForm *ui;
    Database *db;
};

#endif // LOGINFORM_H
