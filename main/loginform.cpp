#include "loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_RegistrationButton_clicked()
{
emit RegistrationRequested();
}

Database *db;
void LoginForm::on_buttonBox_accepted()
{
int userId=db->checkPassword(ui->LoginEdit->text().toStdString(),
                                     ui->PasswordEdit->text().toStdString());
switch(userId)
{
case 0:
    QMessageBox::critical(this,
                          tr("Error"),
                          tr("Wrong Email"));
    return;
case 1:
    QMessageBox::critical(this,
                          tr("Error"),
                          tr("Wrong Password"));
    return;
default:

    QMessageBox::information(0,"Успешно", "Добро пожаловать в чат!");

    emit accepted(userId,ui->LoginEdit->text());
}

}

void LoginForm::on_buttonBox_rejected()
{
   emit rejected();
}

