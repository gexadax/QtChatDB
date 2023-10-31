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
