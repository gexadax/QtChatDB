#include "mainwindow.h"
#include "database.h"
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

    QDir dir(".");
    QStringList filters;
    filters << "*.ini";
    QStringList iniFiles = dir.entryList(filters);

    bool serverIniExists = iniFiles.contains("server.ini");
    bool clientIniExists = iniFiles.contains("client.ini");

    QFile serverFile("server.ini");
    if (serverFile.exists()) {
        ui->tabWidget->setTabEnabled(0, true);
    } else {
        ui->tabWidget->setTabEnabled(0, false);
    }

    QFile clientFile("client.ini");
    if (clientFile.exists()) {
        ui->tabWidget->setTabEnabled(1, true);
    } else {
        ui->tabWidget->setTabEnabled(1, false);
    }

    if (serverIniExists || clientIniExists) {
        ui->stackedWidget->setCurrentIndex(2);
        resize(800, 600);
    } else {
        ui->stackedWidget->setCurrentIndex(0);
    }
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
        QMap<QString, QString> serverData = config.readIniFile("server.ini");

        ui->lineEditDatabase->setPlaceholderText(serverData["DATABASE"]);
        ui->lineEditHostname->setPlaceholderText(serverData["HOSTNAME"]);
        ui->lineEditDatabasename->setPlaceholderText(serverData["DATABASENAME"]);
        ui->lineEditUsername->setPlaceholderText(serverData["USERNAME"]);
        ui->lineEditPassword->setPlaceholderText(serverData["PASSWORD"]);
    }

    if (isClientChecked) {
        Config config;
        config.createServerIni("client.ini");
        QMap<QString, QString> clientData = config.readIniFile("client.ini");

        ui->lineEditDatabase->setPlaceholderText(clientData["DATABASE"]);
        ui->lineEditHostname->setPlaceholderText(clientData["HOSTNAME"]);
        ui->lineEditDatabasename->setPlaceholderText(clientData["DATABASENAME"]);
        ui->lineEditUsername->setPlaceholderText(clientData["USERNAME"]);
        ui->lineEditPassword->setPlaceholderText(clientData["PASSWORD"]);
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
    serverData["DATABASE"] = ui->lineEditDatabase->text();
    serverData["HOSTNAME"] = ui->lineEditHostname->text();
    serverData["DATABASENAME"] = ui->lineEditDatabasename->text();
    serverData["USERNAME"] = ui->lineEditUsername->text();
    serverData["PASSWORD"] = ui->lineEditPassword->text();

    QMap<QString, QString> clientData;
    clientData["DATABASE"] = ui->lineEditDatabase->text();
    clientData["HOSTNAME"] = ui->lineEditHostname->text();
    clientData["DATABASENAME"] = ui->lineEditDatabasename->text();
    clientData["USERNAME"] = ui->lineEditUsername->text();
    clientData["PASSWORD"] = ui->lineEditPassword->text();


    bool isServerChecked = ui->checkBoxServer->isChecked();
    bool isClientChecked = ui->checkBoxClient->isChecked();

    ui->stackedWidget->setCurrentIndex(2);
    resize(800, 600);

    QFile serverFile("server.ini");
    QFile clientFile("client.ini");

    Config config;

    if (isServerChecked) {
        if (!serverDataIsEmpty(serverData)) {
            config.saveIniFile("server.ini", serverData);
        }
    }

    if (isClientChecked) {
        if (!clientDataIsEmpty(clientData)) {
            config.saveIniFile("client.ini", clientData);
        }
    }

    if (serverFile.exists()) {
        ui->tabWidget->setTabEnabled(0, true);
    } else {
        ui->tabWidget->setTabEnabled(0, false);
    }

    if (clientFile.exists()) {
        ui->tabWidget->setTabEnabled(1, true);
    } else {
        ui->tabWidget->setTabEnabled(1, false);
    }

    Database db;
    db.openConnection();
    if (db.createDatabase()) {
        qDebug() << "Database created successfully.";
        if (db.createTable()) {
            qDebug() << "Table created successfully.";
        } else {
            qDebug() << "Error creating table.";
        }
    } else {
        qDebug() << "Error creating the database.";
    }
}
