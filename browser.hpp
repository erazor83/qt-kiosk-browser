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


class BrowserOptions : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString configFile READ _r_configFile )
    Q_PROPERTY(QString forceURL READ _r_forceURL )
    Q_PROPERTY(QString restartCommand READ _r_restartCommand WRITE _w_restartCommand )


public:
    BrowserOptions(void);
    QString configFile;
    QString restartCommand;
    QString forceURL;

    QString _r_configFile() const;
    QString _r_forceURL() const;

    void _w_restartCommand(QString);
    QString _r_restartCommand() const;
};

class Browser: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString Version READ _r_Version )
    Q_PROPERTY(QObject* options WRITE _w_Options )

public:
    //Browser(BrowserOptions *parent = nullptr);
    Browser(QObject *parent = nullptr);
    QObject *options;
    QObject *parent;
    QString _r_Version() const;
    void _w_Options(QObject*);
public slots:
    void restart();
};
#endif // BROWSER_HPP
