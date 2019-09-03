/*
 * qt-kiosk-browser / DBUS Interface
 * Copyright (C) 2019
 * Alexander Krause
 *
 * SPDX-License-Identifier:     GPL-3.0
 */

#ifndef DBUS_IF_SCREENSAVER_H
#define DBUS_IF_SCREENSAVER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlProperty>
 
class DBUS_Interface_ScreenSaver : public QQmlApplicationEngine
{
    Q_OBJECT
    Q_PROPERTY(bool visible READ getVisible WRITE setVisible)
 
public:
    DBUS_Interface_ScreenSaver(QQmlApplicationEngine *qml_engine = nullptr);

    bool getVisible() const;
    void setVisible(bool);

signals:
    void onoffChanged(bool);

public slots:
    void setTimer(int s);
 
private:
    QObject *screenSaverTimer;
    QObject *screenSaver;
};

#endif // DBUS_IF_SCREENSAVER_H
