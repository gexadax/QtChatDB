#include "registrationform.h"
#include "ui_registrationform.h"

RegistrationForm::RegistrationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationForm)
{
    ui->setupUi(this);
}

RegistrationForm::~RegistrationForm()
{
    delete ui;
}

void RegistrationForm::on_LoginButton_clicked()//Login
{
    emit LoginRequested();//emit - отправка сигнала
}


void RegistrationForm::on_buttonBox_accepted()//Ok/Cancel, если принято
{
    if(ui->PasswordlineEdit->text()!=ui->ConfirmPasswordlineEdit->text())//проверка соответствуют ли пароль и повтор пароля для регистрации
    {
        QMessageBox::critical(this,
                              tr("Error"),//tr-вызывается, чтобы (сообщение) стало переводимым
                              tr("Passwords not match"));
        return;
    }
    int userId=addUser(ui->LoginLineEdit->text().//adduser - наша функция из Database.h, которая возращает id пользователя
                                   toStdString());//преобразует в стандартную строку C++

    switch(userId)//выставляем варианты вывода функции addUser
    {
    case 0://некорректное имя
        QMessageBox::critical(this,
                              tr("Error"),//tr-вызывается, чтобы (сообщение) стало переводимым
                              tr("Incorrect Email"));
        return;
    case 2://пользователь существует
        QMessageBox::critical(this,
                              tr("Error"),//tr-вызывается, чтобы (сообщение) стало переводимым
                              tr("Email already exists"));
        return;
    default://все хорошо

        QSqlQuery query;
        query.prepare("INSERT INTO registration_data (email) VALUES (:email)");
        query.bindValue(":email", ui->LoginLineEdit->text());
        query.exec();
        QString Qemail=ui->LoginLineEdit->text();
        QString id_user;
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery("SELECT id_user FROM registration_data WHERE (email=\'"+Qemail+"\')");
        if (model->rowCount() > 0)
        {
            QModelIndex index = model->index(0, 0); // индекс первой ячейки
            id_user = model->data(index).toString(); // получение значения ячейки в виде строки
        }
        query.prepare("UPDATE authorization_data SET password = ? WHERE id_user = ?");
        query.bindValue(0, ui->PasswordlineEdit->text());
        query.bindValue(1, id_user);
        query.exec();
        emit accepted(userId,ui->LoginLineEdit->text());//передаем сигнал, что бы зарегистрирован новый пользователь
    }
}


void RegistrationForm::on_buttonBox_rejected()//Ok/Cancel, если отклонено
{
    emit rejected();
}

