/*
 * qt-kiosk-browser
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     GPL-3.0
 */

#include <QApplication>
#include <QtWebEngine>

#include <QCommandLineParser>
#include <QCommandLineOption>

#include <QDebug>

#include "inputeventhandler.hpp"
#include "browser.hpp"

#ifdef ENABLE_DBUS
#include "dbus_if_browser.h"
#include "dbus_if_browser_interface.h"
#include "dbus_if_browser_adaptor.h"

#include "dbus_if_webview.h"
#include "dbus_if_webview_interface.h"
#include "dbus_if_webview_adaptor.h"

#include "dbus_if_screensaver.h"
#include "dbus_if_screensaver_interface.h"
#include "dbus_if_screensaver_adaptor.h"
#endif

#ifdef ENABLE_FIFO
#include "fifo_reader.h"
#endif

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QCoreApplication::setApplicationName("qt fullscreen browser");
    QCoreApplication::setApplicationVersion(APP_VERSION);

    QCommandLineParser arg_parser;
    arg_parser.addHelpOption();
    arg_parser.addVersionOption();
    const QCommandLineOption urlOption({"u", "url"}, "URL <string>", "url");
    arg_parser.addOption(urlOption);

    const QCommandLineOption configOption({"c", "config"}, "config <file>", "config");
    arg_parser.addOption(configOption);

#ifdef ENABLE_FIFO
    const QCommandLineOption fifoFileOption({"f", "fifo"}, "Use FiFo <file>", "fifo");
    arg_parser.addOption(fifoFileOption);
#endif

    arg_parser.process(app);

    QtWebEngine::initialize();

    BrowserOptions browserOptions;

    qmlRegisterSingletonType<InputEventHandler>(
        "Browser", 1, 1, "Browser", [](QQmlEngine *, QJSEngine *) -> QObject * {
          return new Browser();
        }
    );
    qmlRegisterType<InputEventHandler>("Browser", 1, 0, "InputEventHandler");

    QQmlApplicationEngine engine;


    if (arg_parser.isSet(configOption)) {
        browserOptions.configFile = arg_parser.value(configOption);
    }

    if (arg_parser.isSet(urlOption)) {
        browserOptions.forceURL = arg_parser.value(urlOption);
    }

    //qDebug("browserOptions.forceURL "+browserOptions.forceURL.toLatin1());
    engine.rootContext()->setContextProperty("browserOptions", &browserOptions);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


#ifdef ENABLE_DBUS
    DBUS_Interface_Browser*  pDBUS_Interface_Browser = new DBUS_Interface_Browser(&engine);
    DBUS_Interface_WebView*  pDBUS_Interface_WebView = new DBUS_Interface_WebView(&engine);
    DBUS_Interface_ScreenSaver*  pDBUS_Interface_ScreenSaver = new DBUS_Interface_ScreenSaver(&engine);
    
    // Create interface adaptor
    new DBUS_Interface_BrowserAdaptor(pDBUS_Interface_Browser);
    new DBUS_Interface_WebViewAdaptor(pDBUS_Interface_WebView);
    new DBUS_Interface_ScreenSaverAdaptor(pDBUS_Interface_ScreenSaver);

    // Connect to session bus
    #ifdef DBUS_USE_SYSTEMBUS
    #warning DBUS_USE_SYSTEMBUS is set
    QDBusConnection connection = QDBusConnection::systemBus();
    #else
    QDBusConnection connection = QDBusConnection::sessionBus();
    #endif
    connection.registerObject("/Browser", pDBUS_Interface_Browser);
    connection.registerObject("/WebView", pDBUS_Interface_WebView);
    connection.registerObject("/Screensaver", pDBUS_Interface_ScreenSaver);
    connection.registerService("io.qt.kiosk-browser");
#endif

#ifdef ENABLE_FIFO
    if (arg_parser.isSet("fifo")) {
        QString fifoFileName = arg_parser.value(fifoFileOption);
        //qDebug("fifo filename "+fifoFileName.toLatin1());
        FileReaderThread cReader(fifoFileName,&engine);
        cReader.start();
    }
#endif

    return app.exec();
}
