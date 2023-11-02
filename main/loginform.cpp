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


void LoginForm::on_RegistrationButton_clicked()//Registration
{
emit RegistrationRequested();//emit - отправка сигнала
}

Database *db;
void LoginForm::on_buttonBox_accepted()//  Ok
{
int userId=db->checkPassword(ui->LoginEdit->text().toStdString(),//checkPassword()-из CommandLineInterface.h
                                     ui->PasswordEdit->text().toStdString());
switch(userId)//выставляем варианты вывода функции checkPassword
{
case 0://некорректное имя
    QMessageBox::critical(this,
                          tr("Error"),//tr-вызывается, чтобы (сообщение) стало переводимым
                          tr("Wrong Email"));
    return;
case 1://пользователь существует
    QMessageBox::critical(this,
                          tr("Error"),//tr-вызывается, чтобы (сообщение) стало переводимым
                          tr("Wrong Password"));
    return;
default://все хорошо

    QMessageBox::information(0,"Успешно", "Добро пожаловать в чат!");

    emit accepted(userId,ui->LoginEdit->text());//передаем сигнал, что бы зарегистрирован новый пользователь
}

}


void LoginForm::on_buttonBox_rejected()//  Cancel
{
   emit rejected();
}

