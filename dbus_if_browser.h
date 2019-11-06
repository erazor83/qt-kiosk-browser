/*
 * qt-kiosk-browser / DBUS Interface
 * Copyright (C) 2019
 * Alexander Krause
 *
 * SPDX-License-Identifier:     GPL-3.0
 */

#ifndef DBUS_IF_BROWSER_H
#define DBUS_IF_BROWSER_H
 
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlProperty>

#include "browser.hpp"

class DBUS_Interface_Browser : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString Version READ getVersion )

public:
    DBUS_Interface_Browser(QQmlApplicationEngine *qml_engine = nullptr, Browser* browser  = nullptr);

public slots:
    QString getVersion();
    void restart();

private:
    Browser *browser;
};

#endif // DBUS_IF_BROWSER_H
