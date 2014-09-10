#ifndef LOCALPERSISTERTEST_H
#define LOCALPERSISTERTEST_H

#include <QtTest/QtTest>
#include "LocalPersister.h"
#include <fstream>
#include "FakeDatabasePersister.h"

using namespace std;

class LocalPersisterTest : public QObject
{
    Q_OBJECT
    private slots:
        void filterTest();
};

#endif // LOCALPERSISTERTEST_H
