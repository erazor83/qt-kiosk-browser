/*
 * qt-kiosk-browser
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     GPL-3.0
 */

import QtQuick 2.0
import QtQuick.Window 2.1
import QtWebEngine 1.1
import QtQuick.VirtualKeyboard 2.1
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0
import Browser 1.1

Window {
    id: window

    visibility: Window.FullScreen
    visible: true
    
    signal ssChanged(bool on_off)
    signal urlChanged(string new_url)
    
    Component.onCompleted: {
        console.log("App-Version: "+Browser.Version)

        var xhr = new XMLHttpRequest()

        console.log("== Options ==")
        console.log("config = "+browserOptions.configFile)
        console.log("URL = "+browserOptions.forceURL)
        console.log("=============")

        if (browserOptions.configFile == "") {
            var configFile="settings.json"
        } else {
            var configFile=browserOptions.configFile
        }


        console.log("Load file: " + configFile)
        xhr.open("GET", configFile);

        if (browserOptions.forceURL != "") {
            webView.url = browserOptions.forceURL;
        }
        
        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                if (xhr.responseText.trim().length != 0) {
                    try {
                        console.log("Settings loaded.")
                        var settings = JSON.parse(xhr.responseText)
                        //console.log("settings: "+settings)

                        if (typeof settings["ScreenSaverTimeout"] != "undefined") {
                            screenSaverTimer.interval = parseInt(settings["ScreenSaverTimeout"])
                        }

                        if (typeof settings["RestartTimeout"] != "undefined") {
                            restartTimer.interval = parseInt(settings["RestartTimeout"])
                        }

                        if (typeof settings["UrlTimeout"] != "undefined") {
                            urlTimer.interval = parseInt(settings["UrlTimeout"])
                        }
                        if (typeof settings["UrlTimeoutUrl"] != "undefined") {
                            urlTimer.url = settings["UrlTimeoutUrl"]
                        }
                        
                        if (typeof settings["JsTimeout"] != "undefined") {
                            jsTimer.interval = parseInt(settings["JsTimeout"])
                        }
                        if (typeof settings["JsTimeoutCmd"] != "undefined") {
                            jsTimer.jsCommand = settings["JsTimeoutCmd"]
                        }

                        if (typeof settings["RestartCmd"] != "undefined") {
                            browserOptions.restartCommand = settings["RestartCmd"]
                        }

                        if (browserOptions.forceURL != "") {
                            
                        } else if (typeof settings["URL"] != "undefined") {
                            webView.url = settings["URL"]
                        }
                        
                        if (typeof settings["ignoreInvalidSSL"] != "undefined") {
                            if (settings["ignoreInvalidSSL"]) {
                                console.log("ignoreInvalidSSL is set")
                                webView.ignoreCertErrors = true 
                            }
                        }

                        if (typeof settings["vkeyboardLocale"] != "undefined") {
                            console.log("vkeyboardLocale="+settings["vkeyboardLocale"])
                            VirtualKeyboardSettings.locale=settings["vkeyboardLocale"]
                        }

                        for (var key in settings["WebEngineSettings"]) {
                            if (typeof webView.settings[key] == "undefined") {
                                console.error("Invalid settings property: " + key)
                                continue
                            }

                            webView.settings[key] = settings["WebEngineSettings"][key]
                        }
                        
                        Browser.options=browserOptions
                    } catch (e) {
                        console.error("Failed to parse settings file: " + e)
                    }
                }
            }
        }

        xhr.send();
    }

    WebEngineView {
        id: webView
        objectName: "webView"
        
        url: "http://www.ossystems.com.br"

        property bool ignoreCertErrors: false
        
        onCertificateError: function(error) {
            if (this.ignoreCertErrors) {
                error.ignoreCertificateError()
            }
        }
        
        anchors.fill: parent
    }
    
    ProgressBar{
        id:progressBar
        height: 10
        width:  200
        
        y: parent.height - progressBar.height - 10
        x: parent.width - progressBar.width - 20
        
        visible: webView.loadProgress < 100
        value: webView.loadProgress == 100 ? 0 : webView.loadProgress

        clip: true
        
        background: Rectangle {
            implicitWidth: 200
            implicitHeight: 6
            border.color: "#999999"
            radius: 5
        }
        contentItem: Item {
            implicitWidth: 200
            implicitHeight: 4

            Rectangle {
                id: bar
                width: progressBar.visualPosition * parent.width
                height: parent.height
                radius: 5
            }

            LinearGradient {
                anchors.fill: bar
                start: Qt.point(0, 0)
                end: Qt.point(bar.width, 0)
                source: bar
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#171aa8" }
                    GradientStop { id: grad; position: 0.5; color: Qt.lighter("#171aa8", 2) }
                    GradientStop { position: 1.0; color: "#171aa8" }
                }
                PropertyAnimation {
                    target: grad
                    property: "position"
                    from: 0.1
                    to: 0.9
                    duration: 1000
                    running: true
                    loops: Animation.Infinite
                }
            }
            LinearGradient {
                anchors.fill: bar
                start: Qt.point(0, 0)
                end: Qt.point(0, bar.height)
                source: bar
                gradient: Gradient {
                    GradientStop { position: 0.0; color: Qt.rgba(0,0,0,0) }
                    GradientStop { position: 0.5; color: Qt.rgba(1,1,1,0.3) }
                    GradientStop { position: 1.0; color: Qt.rgba(0,0,0,0.05) }
                }
            }
        }
        PropertyAnimation {
            target: progressBar
            property: "value"
            from: 0
            to: 1
            duration: 5000
            running: true
            loops: Animation.Infinite
        }
    }


    InputPanel {
        id: inputPanel

        y: Qt.inputMethod.visible ? parent.height - inputPanel.height : parent.height

        anchors.left: parent.left
        anchors.right: parent.right
    }

    Rectangle {
        id: screenSaver
        objectName: "screenSaver"
        color: "black"
        visible: false
        anchors.fill: parent

        MouseArea {
            anchors.fill: parent
            //does not work:
            cursorShape: Qt.BlankCursor

            onClicked: {
                screenSaver.visible = false
                window.ssChanged(false)
            }
        }
    }

    InputEventHandler {
        onTriggered: {
            console.error("input triggered, Timer restart")
            screenSaverTimer.restart()
            urlTimer.restart()
            jsTimer.restart()
        }
    }

    Timer {
        id: screenSaverTimer
        objectName: "screenSaverTimer"
        
        interval: 60000 * 20 // 20 minutes
        running: interval > 0
        repeat: false

        onTriggered: {
            if (this.interval > 0) {
                screenSaver.visible = true
                window.ssChanged(true)
                restartTimer.start()
            }
        }
    }

    Timer {
        id: restartTimer
        
        interval: 60000 * 3 // 3 minutes
        repeat: false

        onTriggered: Browser.restart()

        function start() {
            this.running = this.interval > 0
        }
    }
    
    Timer {
        id: urlTimer

        interval: 60000 * 3 // 3 minutes
        running: interval > 0
        repeat: false
        
        property string url: null

        onTriggered: {
            console.error("urlTimer.onTriggered")

            if (this.url) {
                webView.url=this.url
            }
        }

        function start() {
            this.running = this.interval > 0
        }
    }

    Timer {
        id: jsTimer

        interval: 60000 * 3 // 3 minutes
        running: interval > 0
        repeat: false
        
        property string jsCommand: null

        onTriggered: {
            console.error("jsTimer.onTriggered")

            if (this.jsCommand) {
                webView.runJavaScript(
                    this.jsCommand,
                    function(result) {
                        console.log(jsTimer.jsCommand+" | result: "+result)
                    }
                )
            }
        }

        function start() {
            this.running = this.interval > 0
        }
    }
}
