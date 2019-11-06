/*
 * qt-kiosk-browser / DBUS Interface
 * Copyright (C) 2019
 * Alexander Krause
 *
 * SPDX-License-Identifier:     GPL-3.0
 */

#ifndef DBUS_IF_WEBVIEW_H
#define DBUS_IF_WEBVIEW_H
 
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlProperty>

class DBUS_Interface_WebView : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString URL READ getURL WRITE setURL )
 
public:
    DBUS_Interface_WebView(QQmlApplicationEngine *qml_engine = nullptr);
		
    QString getURL() const;
    void setURL(QString);

signals:
    void urlChanged(QString);

public slots:
    void goForward();
    void goBack();
    void reload();
    void navigate(QString);
 
private:
    QObject *webView;
};

#endif // DBUS_IF_WEBVIEW_H
