/*
 * qt-kiosk-browser
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     GPL-3.0
 */

#include "browser.hpp"

#include <QObject>
#include <QVariant>
#include <QProcess>
#include <QFile>

Browser::Browser(QObject *parent): QObject(parent) {
}

void Browser::restart()
{
    qDebug("calling restart");
    if (options != nullptr) {
        QString restartCommand=this->options->property("restartCommand").toString();
        QStringList cmd_split=restartCommand.split(' ');
        QStringList cmd_options;
        for(int i=1; i < cmd_split.size();++i) {
            cmd_options.append(cmd_split[i]);
         }
         qDebug("startDetached");
         QProcess::startDetached(cmd_split[0], cmd_options);
    } else {
         qDebug("No browser options!");
    }
}
QString Browser::_r_Version() const {
    return QString(APP_VERSION);
}
void Browser::_w_Options(QObject* opts) {
    this->options=opts; 
}

BrowserOptions::BrowserOptions(void){
}

QString BrowserOptions::_r_configFile() const {
    return configFile;
}
    
QString BrowserOptions::_r_forceURL() const {
    return forceURL;
}

QString BrowserOptions::_r_restartCommand() const {
    return restartCommand;
}

void BrowserOptions::_w_restartCommand(QString cmd) {
    restartCommand=QString(cmd);
}
