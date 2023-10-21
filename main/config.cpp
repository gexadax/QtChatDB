// config.cpp
#include "config.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

Config::Config() {}

void Config::createServerIni(const QString &filename) {
    QFile file(filename); // Создаем файл
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        // Записываем данные в файл
        stream << "Server Configuration\n\n";
        stream << "DATABASE: QPSQL\n";
        stream << "HOSTNAME: localhost\n";
        stream << "DATABASENAME: chatdb\n";
        stream << "USERNAME: postgres\n";
        stream << "PASSWORD: postgres\n";
        file.close();
    } else {
        // Обработка ошибки открытия файла
        qDebug() << "Ошибка открытия файла " << filename;
    }
}
