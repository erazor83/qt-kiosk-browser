# Qt Kiosk Browser

The _Qt Kiosk Browser_ provides a simple browser which offers a nice set of features for use on a Kiosk device. It supports:

* Out of box screen saver
* Virtual Keyboard
* Highly configurable

Below is a screenshot of it showing the Qt website:

<p align="center">
    <img align="center" src="screenshot.png" height="480px"/>
</p>

## IMPORTANT
With newer QT-versions (I noticed this behavior in qt>5.14) you have to use absolute filenames and the "file://" prefix for config and other file-locations.

You can use the QML_XHR_DUMP=1 environment variable to debug this.

## Features
Enable runtime feature when calling qmake:

### enable D-Bus interface
```
  # qmake "CONFIG+=dbus" .
```

## Settings

The settings file must be a JSON file.

### Available settings

#### vkeyboardLocale

Set the locale for the vertial keyboard.

#### ignoreInvalidSSL

Ignore invalid SSL certificates.

#### ScreenSaverTimeout

Enter in screen saving mode after X milliseconds (0 to disable).

Defaults to 20 minutes.

#### RestartCmd

Shell command to restart the browser. Called via RestartTimeout.

#### RestartTimeout

After entering in screen saving mode, restart browser after X milliseconds (0 to disable).

Defaults to 3 minutes

#### UrlTimeout & UrlTimeoutUrl

Navigate to URL UrlTimeoutUrl after UrlTimeout milliseconds of inactivity (disabled by default).

#### JsTimeout & JsTimeoutCmd

Call Javascript-code JsTimeoutCmd after JsTimeout milliseconds of inactivity (disabled by default).

#### JsOnPageLoadCmd & JsOnPageLoadCmdFile

Call Javascript-code JsOnPageLoadCmd after ANY page has been loaded (disabled by default). This is usefull for some auto-login feature. Alternatively you can use JsOnPageLoadCmdFile to use a javascript file.

#### WebEngineSettings

Configure browser properties and generic attributes, such as JavaScript support, focus behavior, and access to remote content.

Se all available properties at: https://doc.qt.io/qt-5.11/qml-qtwebengine-webenginesettings.html#properties

Example:

```json
{
    "ScreenSaverTimeout":   10000,
    "RestartCmd":           2000,
    "RestartTimeout":       2000,
    "UrlTimeout":           10000,
    "UrlTimeoutUrl":        "http://google.de",
    "JsTimeout":            "5000",
    "JsTimeoutCmd":         "window.history.back()",
    "ignoreInvalidSSL":     true,
    "JsOnPageLoadCmd":      "document.body.style.backgroundColor = \"red\";",
    "JsOnPageLoadCmdFile":  "file:///home/erazor/git/qt-kiosk-browser/on-loaded.js",

    "WebEngineSettings": {
        "javascriptEnabled": false
    }
}
```

### D-Bus interface
```
  > qdbus io.qt.kiosk-browser
/
/Screensaver
/WebView

  > qdbus io.qt.kiosk-browser /WebView
property readwrite QString local.DBUS_Interface_WebView.URL
signal void local.DBUS_Interface_WebView.urlChanged(QString)
method void local.DBUS_Interface_WebView.goBack()
method void local.DBUS_Interface_WebView.goForward()
method void local.DBUS_Interface_WebView.reload()
signal void org.freedesktop.DBus.Properties.PropertiesChanged(QString interface_name, QVariantMap changed_properties, QStringList invalidated_properties)
method QDBusVariant org.freedesktop.DBus.Properties.Get(QString interface_name, QString property_name)
method QVariantMap org.freedesktop.DBus.Properties.GetAll(QString interface_name)
method void org.freedesktop.DBus.Properties.Set(QString interface_name, QString property_name, QDBusVariant value)
method QString org.freedesktop.DBus.Introspectable.Introspect()
method QString org.freedesktop.DBus.Peer.GetMachineId()
method void org.freedesktop.DBus.Peer.Ping()

  > qdbus io.qt.kiosk-browser /WebView org.freedesktop.DBus.Properties.Set local.DBUS_Interface_WebView URL "http://google.de"
  
  > qdbus io.qt.kiosk-browser /WebView org.freedesktop.DBus.Properties.Get local.DBUS_Interface_WebView URL
https://www.google.de/
```
