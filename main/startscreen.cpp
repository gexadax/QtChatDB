#include "startscreen.h"
#include "ui_startscreen.h"

StartScreen::StartScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartScreen)
{
    ui->setupUi(this);

    connect(ui->loginWidget, &LoginForm::RegistrationRequested,this, &StartScreen::setRegistrationForm);
    connect(ui->loginWidget, &LoginForm::accepted,this, &StartScreen::onLoggedIn);
    connect(ui->loginWidget, &LoginForm::rejected,this, &StartScreen::onRejectRequested);
    connect(ui->RegistrationWidget, &RegistrationForm::LoginRequested,this, &StartScreen::setLoginForm);
    connect(ui->RegistrationWidget, &RegistrationForm::accepted,this, &StartScreen::onLoggedIn);
    connect(ui->RegistrationWidget, &RegistrationForm::rejected,this, &StartScreen::onRejectRequested);
}

StartScreen::~StartScreen()
{
    delete ui;
}

void StartScreen::setLoginForm()
{
    QWidget* widget = findChild<QWidget*>("loginWidget");
    ui->stackedWidget->setCurrentWidget(widget);
}

void StartScreen::setRegistrationForm()
{
    QWidget* widget = findChild<QWidget*>("RegistrationWidget");
    ui->stackedWidget->setCurrentWidget(widget);
}

void StartScreen::onLoggedIn(int userId,QString Qemail)
{
  m_user_id=userId;
    m_Qemail =Qemail;
  accept();
}

void StartScreen::onRejectRequested()
{
  reject();
}

int StartScreen::user_id() const
{
    return m_user_id;
}

QString StartScreen::getQemail() const
{
    return m_Qemail;
}

