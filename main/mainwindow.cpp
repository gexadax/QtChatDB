#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "config.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Связываем нажатие кнопки "Next" с обработчиком
    connect(ui->pushButtonNext, &QPushButton::clicked, this, &MainWindow::createServerIni);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::createServerIni() {
    Config config; // Создаем объект класса Config
    config.createServerIni(); // Вызываем метод createServerIni
}

void MainWindow::on_pushButtonNext_clicked() {
    // Ваш код для обработки нажатия кнопки "Next"
    ui->stackedWidget->setCurrentIndex(1);
}
