/*
 * qt-kiosk-browser / DBUS Interface
 * Copyright (C) 2019
 * Alexander Krause
 *
 * SPDX-License-Identifier:     GPL-3.0
 */

#include "browser.hpp"
#include "dbus_if_screensaver.h"

DBUS_Interface_ScreenSaver::DBUS_Interface_ScreenSaver(QQmlApplicationEngine *qml_engine, Browser* browser)
{
    screenSaverTimer = qml_engine->rootObjects().at(0)->findChild<QObject*>("screenSaverTimer");
    screenSaver = qml_engine->rootObjects().at(0)->findChild<QObject*>("screenSaver");
}
 
bool DBUS_Interface_ScreenSaver::getVisible() const
{
    if (QQmlProperty(screenSaver,"visible").read().toString()=="1") {
         return true;
    } else {
         return false;
    }
}
 
void DBUS_Interface_ScreenSaver::setVisible(bool on_off)
{
    emit onoffChanged(on_off);
    QQmlProperty(screenSaver,"visible").write(on_off);
}


void DBUS_Interface_ScreenSaver::setTimer(int s)
{
    if (s>0) {
        QQmlProperty(screenSaverTimer,"interval").write(s);
        QMetaObject::invokeMethod(screenSaverTimer,"start");
    } else {
        QMetaObject::invokeMethod(screenSaverTimer,"stop");
    }
}
