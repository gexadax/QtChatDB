#ifndef SERVERFORM_H
#define SERVERFORM_H

#include <QWidget>
#include "ui_serverform.h"

class ServerFormWindow : public QWidget {
    Q_OBJECT

public:
    ServerFormWindow(QWidget *parent = nullptr);

private:
    Ui::ServerForm *ui;

private slots:
    void onPushButtonClicked();
    void onPushButtonBanClicked();
};

#endif // SERVERFORM_H
