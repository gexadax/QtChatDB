#include "config.h"
#include <QFile>
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
        stream << "PASSWORD: postgres\n";
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
