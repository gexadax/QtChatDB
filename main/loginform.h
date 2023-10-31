#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QFormLayout>

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();
    QFormLayout* getFormLayoutLogin();

private:
    Ui::LoginForm *ui;
};

#endif // LOGINFORM_H
