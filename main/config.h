#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
//#include <QMap>

class Config
{
public:
    Config();
    void createServerIni(const QString &filename);
    void saveIniFile(const QString &filename, const QMap<QString, QString> &data);
    QMap<QString, QString> readIniFile(const QString &filename);

};

#endif // CONFIG_H
