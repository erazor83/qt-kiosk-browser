/*
 * qt-kiosk-browser
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     GPL-3.0
 */

#ifndef BROWSER_HPP
#define BROWSER_HPP

#include <QObject>

class Browser: public QObject
{
    Q_OBJECT

public:
    Browser(QObject *parent = nullptr);

public slots:
    void restart();
};

class BrowserOptions : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString configFile READ _r_configFile )
    Q_PROPERTY(QString forceURL READ _r_forceURL )


public:
    BrowserOptions(QObject *parent = nullptr);
    QString configFile;
    QString forceURL;

    QString _r_configFile() const;
    QString _r_forceURL() const;
};
#endif // BROWSER_HPP
