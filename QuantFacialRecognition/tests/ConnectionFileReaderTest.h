#ifndef CONNECTIONFILEREADERTEST_H
#define CONNECTIONFILEREADERTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include "ConnectionFileReader.h"

class ConnectionFileReaderTest : public QObject
{
    Q_OBJECT
    private slots:
        void parseTest();

};

#endif // CONNECTIONFILEREADERTEST_H
