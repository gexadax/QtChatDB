#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "database.h"
//#include <QMainWindow>
//#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slot_pushButtonNext_clicked();
    void slot_pushButtonPreview_clicked();
    void slot_pushButtonFinish_clicked();
    void updateNextButtonState();


private:
    Ui::MainWindow *ui;
    Database *db;
    void createServerIni(const QString &filename);
    void saveIniFile(const QString &filename, const QMap<QString, QString> &data);

};

bool serverDataIsEmpty(const QMap<QString, QString> &data);
bool clientDataIsEmpty(const QMap<QString, QString> &data);

#endif // MAINWINDOW_H
