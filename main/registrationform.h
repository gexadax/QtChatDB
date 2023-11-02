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
    void LoginRequested();
    void accepted(int userId,QString Qemail);
    void rejected();

private slots:
    void on_LoginButton_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::RegistrationForm *ui;

};

#endif // REGISTRATIONFORM_H
