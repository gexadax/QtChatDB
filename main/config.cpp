#include "config.h"
#include <QTextStream>
#include <QDebug>

Config::Config() {}

void Config::createServerIni() {
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
