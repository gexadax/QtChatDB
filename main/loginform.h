#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <memory>
#include "database.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();
signals:
    void RegistrationRequested();//функция для переключения на RegistrationForm для кнопки Registration
    void accepted(int userId,QString Qemail);// если принято
    void rejected();// если отклонено
private slots:
    void on_RegistrationButton_clicked();

    void on_buttonBox_accepted();//Ok\ Cancel если принято

    void on_buttonBox_rejected();//Ok\ Cancel если отклонено

private:
    Ui::LoginForm *ui;

};

#endif // LOGINFORM_H
