#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void createServerIni(const QString& filename);

public slots:
    void slot_pushButtonNext_clicked();
    void slot_pushButtonPreview_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
