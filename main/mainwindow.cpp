#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "config.h"
#include <QDir>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->pushButtonNext, &QPushButton::clicked, this, &MainWindow::slot_pushButtonNext_clicked);
    connect(ui->pushButtonPreview, &QPushButton::clicked, this, &MainWindow::slot_pushButtonPreview_clicked);
    connect(ui->pushButtonFinish, &QPushButton::clicked, this, &MainWindow::slot_pushButtonFinish_clicked);
    connect(ui->checkBoxServer, &QCheckBox::stateChanged, this, &MainWindow::updateNextButtonState);
    connect(ui->checkBoxClient, &QCheckBox::stateChanged, this, &MainWindow::updateNextButtonState);
    ui->pushButtonNext->setEnabled(false);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateNextButtonState() {
    bool isServerChecked = ui->checkBoxServer->isChecked();
    bool isClientChecked = ui->checkBoxClient->isChecked();

    ui->pushButtonNext->setEnabled(isServerChecked || isClientChecked);
}

void MainWindow::slot_pushButtonNext_clicked() {
    bool isServerChecked = ui->checkBoxServer->isChecked();
    bool isClientChecked = ui->checkBoxClient->isChecked();

    if (isServerChecked) {
        Config config;
        config.createServerIni("server.ini");
    }

    if (isClientChecked) {
        Config config;
        config.createServerIni("client.ini");
    }

    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::slot_pushButtonPreview_clicked() {
    int currentIndex = ui->stackedWidget->currentIndex();
    if (currentIndex > 0) {
        ui->stackedWidget->setCurrentIndex(currentIndex - 1);
    }

    QDir dir(".");
    QStringList filters;
    filters << "*.ini";
    QStringList iniFiles = dir.entryList(filters);

    foreach (const QString &iniFile, iniFiles) {
        QFile::remove(iniFile);
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

    bool isServerChecked = ui->checkBoxServer->isChecked();
    bool isClientChecked = ui->checkBoxClient->isChecked();

    if (isServerChecked) {
        Config config;
        config.saveIniFile("server.ini", serverData);
    }

    if (isClientChecked) {
        Config config;
        config.saveIniFile("client.ini", serverData);
    }

    ui->stackedWidget->setCurrentIndex(1);
}
