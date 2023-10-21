#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "config.h"
#include <QFile>
#include <QDir>
#include <QStackedWidget>
#include <QDataStream>
#include <QDebug>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Connect your buttons to slots
    connect(ui->pushButtonNext, &QPushButton::clicked, this, &MainWindow::slot_pushButtonNext_clicked);
    connect(ui->pushButtonPreview, &QPushButton::clicked, this, &MainWindow::slot_pushButtonPreview_clicked);
    connect(ui->pushButtonFinish, &QPushButton::clicked, this, &MainWindow::slot_pushButtonFinish_clicked);
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

void MainWindow::saveIniFile(const QString &filename, const QMap<QString, QString> &data) {
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        // Записываем данные в ini файл
        foreach (const QString &key, data.keys()) {
            stream << key << ": " << data[key] << "\n";
        }

        file.close();
    } else {
        qDebug() << "Ошибка открытия файла " << filename;
    }
}

void MainWindow::slot_pushButtonFinish_clicked() {
    QMap<QString, QString> serverData;
    serverData["DATABASE"] = ui->textEditDatabase->toPlainText();
    serverData["HOSTNAME"] = ui->textEditHostname->toPlainText();
    serverData["DATABASENAME"] = ui->textEditDatabasename->toPlainText();
    serverData["USERNAME"] = ui->textEditUsername->toPlainText();
    serverData["PASSWORD"] = ui->textEditPassword->toPlainText();

    QMap<QString, QString> clientData;
    clientData["DATABASE"] = ui->textEditDatabase->toPlainText();
    clientData["HOSTNAME"] = ui->textEditHostname->toPlainText();
    clientData["DATABASENAME"] = ui->textEditDatabasename->toPlainText();
    clientData["USERNAME"] = ui->textEditUsername->toPlainText();
    clientData["PASSWORD"] = ui->textEditPassword->toPlainText();

    // Определяем, выбран ли чекбокс "Server"
    bool isServerChecked = ui->checkBoxServer->isChecked();

    // Определяем, выбран ли чекбокс "Client"
    bool isClientChecked = ui->checkBoxClient->isChecked();

    if (isServerChecked) {
        saveIniFile("server.ini", serverData);
    }

    if (isClientChecked) {
        saveIniFile("client.ini", serverData);
    }

    // Переключаемся на следующую страницу
    ui->stackedWidget->setCurrentIndex(1);
}


