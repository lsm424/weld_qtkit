#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>
#include <QVariant>
#include <QString>

class Config {

public:
    static Config& Instance();
    QVariant GetValue(QString key, QVariant val="");

protected:
    Config();

    Config(const Config &config) = delete;
    const Config& operator=(const Config &config) = delete;

    QSettings *setting;
    static Config config;  //
};

#endif // CONFIG_H
