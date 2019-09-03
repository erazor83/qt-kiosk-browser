/*
 * qt-kiosk-browser / FiFo reader
 * Copyright (C) 2019
 * Alexander Krause
 *
 * SPDX-License-Identifier:     GPL-3.0
 */

#include "fifo_reader.h"

#include <QtWebEngine>
#include <QDebug>
#include <QFile>

FileReaderThread::FileReaderThread(QString filename, QQmlEngine *qml_engine): filename(filename),qml_engine(qml_engine)
{
}

void FileReaderThread::run()
{
    qDebug("start thread");
    qDebug("reading "+filename.toLatin1());

    QFile file(filename);
    file.open(QFile::ReadOnly);
    QTextStream in(&file);
    QString line = in.readLine();
    while (!line.isNull())
    {
        line = in.readLine();
        qDebug("fifo line "+line.toLatin1());
    }
    qDebug("thread end");
}
