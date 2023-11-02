#include "loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
}

QFormLayout* LoginForm::getFormLayoutLogin() {
    return ui->formLayoutLogin;
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_pushButtonRegister_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    emit RegistrationRequested();
}


void LoginForm::on_pushButtonOk_clicked()
{
    int userId = db->checkPassword(ui->lineEditLogin->text().toStdString(), ui->lineEditPassword->text().toStdString());

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

        emit accepted(userId,ui->lineEditLogin->text());
    }
}

void LoginForm::on_pushButtonCancel_clicked()
{
    this->close();
    db->closeConnection();
    emit rejected();
}

void LoginForm::on_pushButtonRegistrationCancel_clicked()
{
    this->close();
    db->closeConnection();
}

void LoginForm::on_pushButtonRegistrationOk_clicked()
{
    if (ui->lineEditRegistrationPassword->text() != ui->lineEditRegistrationConfirmPassword->text())
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Passwords not match"));
        return;
    }

    int userId = addUser(ui->lineEditRegistrationLogin->text().toStdString());

    switch (userId)
    {
    case 0:
        QMessageBox::critical(this, tr("Error"), tr("Incorrect Email"));
        return;
    case 2:
        QMessageBox::critical(this, tr("Error"), tr("Email already exists"));
        return;
    default:

        QSqlQuery query;
        query.prepare("INSERT INTO registration_data (email) VALUES (:email)");
        query.bindValue(":email", ui->lineEditRegistrationLogin->text());
        query.exec();
        QString Qemail=ui->lineEditRegistrationLogin->text();
        QString id_user;
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery("SELECT id_user FROM registration_data WHERE (email=\'"+Qemail+"\')");
        if (model->rowCount() > 0)
        {
            QModelIndex index = model->index(0, 0);
            id_user = model->data(index).toString();
        }
        query.prepare("UPDATE authorization_data SET password = ? WHERE id_user = ?");
        query.bindValue(0, ui->lineEditRegistrationPassword->text());
        query.bindValue(1, id_user);
        query.exec();
        emit accepted(userId,ui->lineEditRegistrationLogin->text());
    }
}

