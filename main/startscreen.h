#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QDialog>

namespace Ui {
class StartScreen;
}

class StartScreen : public QDialog
{
    Q_OBJECT

public:
    explicit StartScreen(QWidget *parent = nullptr);
    ~StartScreen();
    void setLoginForm();//функция для изменения индекса страницы на 0
    void setRegistrationForm();//функция для изменения индекса страницы на 1
    int user_id() const;

    QString getQemail() const;

public slots:
    void onLoggedIn(int userId,QString Qemail);//ловим из сигнала нажатие на кнопку ОК
    void onRejectRequested();//ловим из сигнала нажатие на кнопку ОК
private:
    Ui::StartScreen *ui;
    int m_user_id;
    QString m_Qemail;

};

#endif // STARTSCREEN_H
