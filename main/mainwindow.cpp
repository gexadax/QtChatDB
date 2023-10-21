#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "config.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Связываем нажатие кнопки "Next" с обработчиком
    connect(ui->pushButtonNext, &QPushButton::clicked, this, &MainWindow::slot_pushButtonNext_clicked);
    connect(ui->pushButtonPreview, &QPushButton::clicked, this, &MainWindow::slot_pushButtonPreview_clicked);



}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::createServerIni() {
    Config config; // Создаем объект класса Config
    config.createServerIni(); // Вызываем метод createServerIni без аргументов
}

void MainWindow::slot_pushButtonNext_clicked() {
    // Код для обработки нажатия кнопки "Next"
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::slot_pushButtonPreview_clicked() {
    int currentIndex = ui->stackedWidget->currentIndex();
    if (currentIndex > 0) { // Проверяем, что текущая страница не является первой
        ui->stackedWidget->setCurrentIndex(currentIndex - 1);
    }
    // Проверка и удаление файла server.ini по расширению ini
    else if (QFile::exists("server.ini")) {
        QFile::remove("server.ini");
    }
}
