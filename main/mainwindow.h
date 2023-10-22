#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
    void createServerIni(const QString &filename);
    void saveIniFile(const QString &filename, const QMap<QString, QString> &data);
};

#endif // MAINWINDOW_H
