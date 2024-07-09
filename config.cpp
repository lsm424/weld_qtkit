#include "config.h"

Config Config::config;

Config& Config::Instance() {
    return config;
}

Config::Config() {
    this->setting = new QSettings("config.ini", QSettings::IniFormat);
}

QVariant Config::GetValue(QString key, QVariant val) {
    return this->setting->value(key, val);
}
