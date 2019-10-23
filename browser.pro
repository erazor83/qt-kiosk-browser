TEMPLATE = app

DEFINES += APP_VERSION=\\\"1.2\\\"

QT += qml quick core gui webengine webenginewidgets

contains(CONFIG,"dbus") {
  message("Enabling DBUS support!")
  QT += dbus
  DEFINES += ENABLE_DBUS

contains(CONFIG,"dbus-systembus") {
  message("Using systembus")
  DEFINES += DBUS_USE_SYSTEMBUS
}

  #DBUS_ADAPTORS += webview screensaver
  #DBUS_INTERFACES += webview screensaver
  #webview.files = dbus_if_screensaver.xml
  #screensaver.files = dbus_if_screensaver.xml
  #webview.header_flags = -lFoo
  #webview.source_flags = -lFoo

  DBUS_INTERFACES += dbus_if_browser.xml dbus_if_webview.xml dbus_if_screensaver.xml
  DBUS_ADAPTORS += dbus_if_browser.xml dbus_if_webview.xml dbus_if_screensaver.xml

  
  HEADERS += dbus_if_screensaver.h dbus_if_webview.h dbus_if_browser.h
  SOURCES += dbus_if_screensaver.cpp dbus_if_webview.cpp dbus_if_browser.cpp

  #SOURCES += dbus_if_screensaver_adaptor.cpp dbus_if_webview_adaptor.cpp
  #SOURCES += dbus_if_screensaver_interface.cpp dbus_if_webview_interface.cpp
}

contains(CONFIG,"fifo") {
  warning("Enabling fifo support, untested!")
  DEFINES += ENABLE_FIFO
  HEADERS += fifo_reader.h
  SOURCES += fifo_reader.cpp
}

#qdbuscpp2xml -A dbus_if_screensaver.h -o dbus_if_screensaver.xml
#qdbuscpp2xml -A dbus_if_webview.h -o dbus_if_webview.xml

CONFIG += c++11

TARGET = qt-kiosk-browser

HEADERS += \
  inputeventhandler.hpp \
  browser.hpp

SOURCES += \
  main.cpp \
  inputeventhandler.cpp \
  browser.cpp

RESOURCES += resources.qrc

target.path = $$PREFIX/bin

INSTALLS += target
