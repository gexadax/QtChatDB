#include "startscreen.h"
#include "ui_startscreen.h"

StartScreen::StartScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartScreen)
{
    ui->setupUi(this);


    connect(ui->loginWidget, &LoginForm::RegistrationRequested,this, &StartScreen::setRegistrationForm);//обеспечивает связь между виджетом и функциями
    connect(ui->loginWidget, &LoginForm::accepted,this, &StartScreen::onLoggedIn);//чтобы  сразу после нажатия ok(accepted),начиналась функция onLoggedIn
    connect(ui->loginWidget, &LoginForm::rejected,this, &StartScreen::onRejectRequested);//чтобы  сразу после нажатия cancel(rejected),начиналась функция onRejectRequested
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
    //ui->stackedWidget->setCurrentWidget(0);//0-индекс страницы(page) виджет LoginForm
    QWidget* widget = findChild<QWidget*>("loginWidget");
    ui->stackedWidget->setCurrentWidget(widget);
}

void StartScreen::setRegistrationForm()
{
    //ui->stackedWidget->setCurrentWidget(1);//1- индекс страницы(page) виджет RegistrationForm
    QWidget* widget = findChild<QWidget*>("RegistrationWidget");//ищет виджет по названию
    ui->stackedWidget->setCurrentWidget(widget);
}

void StartScreen::onLoggedIn(int userId,QString Qemail)
{
  m_user_id=userId;
    m_Qemail =Qemail;
  accept();// чтоб работала ok на авторизации
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

