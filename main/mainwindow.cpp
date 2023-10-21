#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "config.h"
#include <QFile>
#include <QDir>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Связываем нажатие кнопки "Next" с обработчиком
    connect(ui->pushButtonNext, &QPushButton::clicked, this, &MainWindow::slot_pushButtonNext_clicked);
    connect(ui->pushButtonPreview, &QPushButton::clicked, this, &MainWindow::slot_pushButtonPreview_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::createServerIni(const QString &filename) {
    Config config;
    config.createServerIni(filename);
}

void MainWindow::slot_pushButtonNext_clicked() {
    // Определяем, выбран ли чекбокс "Server"
    bool isServerChecked = ui->checkBoxServer->isChecked();

    // Определяем, выбран ли чекбокс "Client"
    bool isClientChecked = ui->checkBoxClient->isChecked();

    // Если выбран чекбокс "Server"
    if (isServerChecked) {
        createServerIni("server.ini");
    }

    // Если выбран чекбокс "Client"
    if (isClientChecked) {
        createServerIni("client.ini");
    }

    // Переключаемся на следующую страницу
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::slot_pushButtonPreview_clicked() {
    int currentIndex = ui->stackedWidget->currentIndex();
    if (currentIndex > 0) {
        ui->stackedWidget->setCurrentIndex(currentIndex - 1);
    }

    // Удаление всех файлов с расширением .ini
    QDir dir(".");
    QStringList filters;
    filters << "*.ini";
    QStringList iniFiles = dir.entryList(filters);

    foreach (const QString &iniFile, iniFiles) {
        QFile::remove(iniFile);
    }
}



