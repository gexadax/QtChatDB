#include "serverform.h"
#include "ui_serverform.h"

ServerFormWindow::ServerFormWindow(QWidget *parent) : QWidget(parent), ui(new Ui::ServerForm)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &ServerFormWindow::onPushButtonClicked);
    connect(ui->pushButtonBan, &QPushButton::clicked, this, &ServerFormWindow::onPushButtonBanClicked);
}

void ServerFormWindow::onPushButtonClicked() {

}

void ServerFormWindow::onPushButtonBanClicked() {

}
