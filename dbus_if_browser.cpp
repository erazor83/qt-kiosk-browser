/*
 * qt-kiosk-browser / DBUS Interface
 * Copyright (C) 2019
 * Alexander Krause
 *
 * SPDX-License-Identifier:     GPL-3.0
 */

#include "browser.hpp"
#include "dbus_if_browser.h"

DBUS_Interface_Browser::DBUS_Interface_Browser(QQmlApplicationEngine *qml_engine, Browser* browser)
{
    this->browser = browser;
    if (!this->browser) {
        qDebug("Got no browser instance!");
    }
}
 
QString DBUS_Interface_Browser::getVersion(void)
{
    return this->browser->getVersion();
}

void DBUS_Interface_Browser::restart(void)
{
    this->browser->restart();
}
