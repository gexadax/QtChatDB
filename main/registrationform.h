#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H
#include "database.h"


namespace Ui {
class RegistrationForm;
}

class RegistrationForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationForm(QWidget *parent = nullptr);
    ~RegistrationForm();

signals:
    void LoginRequested();//функция для переключения на LoginForm
    void accepted(int userId,QString Qemail);// если принято
    void rejected();// если отклонено

private slots:
    void on_LoginButton_clicked();

    void on_buttonBox_accepted();//Ok\ Cancel если принято

    void on_buttonBox_rejected();//Ok\ Cancel если отклонено

private:
    Ui::RegistrationForm *ui;

};

#endif // REGISTRATIONFORM_H
