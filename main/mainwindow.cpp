#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Связываем нажатие кнопки "Next" с обработчиком
    connect(ui->pushButtonNext, &QPushButton::clicked, this, &MainWindow::createServerIni);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::createServerIni() {
    if (ui->checkBoxServer->isChecked()) {
        // Создаем файл server.ini в текущей директории
        QFile file("server.ini");

        // Пытаемся открыть файл для записи
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            // Записываем данные в файл
            stream << "Server Configuration\n\n";
            stream << "DATABASE: QPSQL\n";
            stream << "HOSTNAME: localhost\n";
            stream << "DATABASENAME: chatdb\n";
            stream << "USERNAME: postgres\n";
            stream << "PASSWORD: postgres\n";


            // Закрываем файл
            file.close();
        } else {
            // Обработка ошибки открытия файла
            qDebug() << "Ошибка открытия файла server.ini";
        }
    }
}
