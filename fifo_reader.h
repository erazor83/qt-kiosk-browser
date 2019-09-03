/*
 * qt-kiosk-browser / FiFo reader
 * Copyright (C) 2019
 * Alexander Krause
 *
 * SPDX-License-Identifier:     GPL-3.0
 */

#ifndef FIFO_READER_H
#define FIFO_READER_H

#include <QtWebEngine>
#include <QObject>
#include <QThread>
#include <QString>

class FileReaderThread : public QThread
{
public:
    explicit FileReaderThread(QString filename,QQmlEngine *qml_engine);

    void run();
private:
    QString filename;
    QQmlEngine *qml_engine;
};


/*
class Reader : public QObject
{
    Q_OBJECT
public:
public slots:
    void readFile(QString fileName);
}

void Reader::readFile(QString fileName)
{
    QByteArray result;

    QFile file(fileName);
    file.open(QFile::ReadOnly);
    // ... read the data and fill the result buffer
    file.close();

    emit fileRead(fileName, result);
}
*/
#endif //FIFO_READER_H
