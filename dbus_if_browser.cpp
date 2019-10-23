/*
 * qt-kiosk-browser / DBUS Interface
 * Copyright (C) 2019
 * Alexander Krause
 *
 * SPDX-License-Identifier:     GPL-3.0
 */

#include "dbus_if_browser.h"

DBUS_Interface_Browser::DBUS_Interface_Browser(QQmlApplicationEngine *qml_engine)
{
    browser = qml_engine->rootObjects().at(0)->findChild<QObject*>("Browser");
}
 
QString DBUS_Interface_Browser::getVersion(void)
{
    return QString(APP_VERSION);
}
