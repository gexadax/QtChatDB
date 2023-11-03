#include "mainwindow.h"
#include "serverform.h"
#include "loginform.h"
#include "ui_mainwindow.h"
#include "startscreen.h"
#include "clientform.h"

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
    db = new Database;
}

MainWindow::~MainWindow() {
    if (db) {
        delete db;
    }
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

    ui->stackedWidgetConfig->setCurrentIndex(1);
}

void MainWindow::slot_pushButtonPreview_clicked() {
    int currentIndex = ui->stackedWidgetConfig->currentIndex();
    if (currentIndex > 0) {
        ui->stackedWidgetConfig->setCurrentIndex(currentIndex - 1);
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

    bool serverIniExists = QFile::exists("server.ini");
    bool clientIniExists = QFile::exists("client.ini");

    if (isServerChecked) {
        ServerForm *serverForm = new ServerForm;
        serverForm->show();
    }

    if (isClientChecked) {
        ClientForm* clientForm = ClientForm::createClient();

        if (clientForm) {
            clientForm->setAttribute(Qt::WA_DeleteOnClose);
            clientForm->show();
        } else {
            qDebug() << "Failed to create ClientForm.";
        }
    }

    if (isServerChecked || isClientChecked) {
        if (db->createDatabase()) {
            qDebug() << "Database created successfully.";
            if (db->createTable()) {
                qDebug() << "Table created successfully.";
            } else {
                qDebug() << "Error creating table.";
            }
        } else {
            qDebug() << "Error creating the database.";
        }
    }
    this->close();
}


