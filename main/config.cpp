#include "config.h"
#include "mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

Config::Config() {}

void Config::createServerIni(const QString &filename) {
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << "Server Configuration\n\n";
        stream << "DATABASE: QPSQL\n";
        stream << "HOSTNAME: localhost\n";
        stream << "DATABASENAME: chatdb\n";
        stream << "USERNAME: postgres\n";
        stream << "PASSWORD: dfbdvtgh\n";
        file.close();
    } else {
        qDebug() << "Error opening file " << filename;
    }
}

void Config::saveIniFile(const QString &filename, const QMap<QString, QString> &data) {
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        foreach (const QString &key, data.keys()) {
            stream << key << ": " << data[key] << "\n";
        }
        file.close();
    } else {
        qDebug() << "Error opening file " << filename;
    }
}

QMap<QString, QString> Config::readIniFile(const QString &filename) {
    QMap<QString, QString> data;
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            QStringList parts = line.split(":");
            if (parts.size() == 2) {
                data[parts[0].trimmed()] = parts[1].trimmed();
            }
        }
        file.close();
    } else {
        qDebug() << "Error opening file " << filename;
    }
    return data;
}

bool serverDataIsEmpty(const QMap<QString, QString> &data) {
    return data["DATABASE"].isEmpty() && data["HOSTNAME"].isEmpty() &&
           data["DATABASENAME"].isEmpty() && data["USERNAME"].isEmpty() &&
           data["PASSWORD"].isEmpty();
}

bool clientDataIsEmpty(const QMap<QString, QString> &data) {
    return data["DATABASE"].isEmpty() && data["HOSTNAME"].isEmpty() &&
           data["DATABASENAME"].isEmpty() && data["USERNAME"].isEmpty() &&
           data["PASSWORD"].isEmpty();
}
