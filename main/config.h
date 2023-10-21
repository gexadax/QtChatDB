// config.h
#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

class Config
{
public:
    Config();
    void createServerIni(const QString &filename);
};

#endif // CONFIG_H
