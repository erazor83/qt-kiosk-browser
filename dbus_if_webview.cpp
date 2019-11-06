/*
 * qt-kiosk-browser / DBUS Interface
 * Copyright (C) 2019
 * Alexander Krause
 *
 * SPDX-License-Identifier:     GPL-3.0
 */

#include "dbus_if_webview.h"

DBUS_Interface_WebView::DBUS_Interface_WebView(QQmlApplicationEngine *qml_engine)
{
    webView = qml_engine->rootObjects().at(0)->findChild<QObject*>("webView");
    if (!webView) {
        qDebug("QML-Object 'webView' not found!");
    }
}
 
QString DBUS_Interface_WebView::getURL() const
{
    QString response=QQmlProperty(webView,"url").read().toString();
    //qDebug("D-BUS: getURL()");
    //qDebug("Response: "+response.toLatin1());
    return response;
}

void DBUS_Interface_WebView::navigate(QString url)
{
    this->setURL(url);
}

void DBUS_Interface_WebView::setURL(QString url)
{
    qDebug("D-BUS: setURL()");
    emit urlChanged(url);
    QQmlProperty(webView, "url").write(url);
}

void DBUS_Interface_WebView::goForward()
{
    qDebug("D-BUS: goForward()");
    QMetaObject::invokeMethod(webView,"goForward");
}

void DBUS_Interface_WebView::goBack()
{
    qDebug("D-BUS: goBack()");
    QMetaObject::invokeMethod(webView,"goBack");
}

void DBUS_Interface_WebView::reload()
{
    QMetaObject::invokeMethod(webView,"reload");
}
