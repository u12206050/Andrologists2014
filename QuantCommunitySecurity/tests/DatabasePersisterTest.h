#ifndef DATABASEPERSISTERTEST_H
#define DATABASEPERSISTERTEST_H

#include <QtTest/QtTest>

#include "DatabasePersister.h"
#include "DatabaseConnection.h"

class DatabasePersisterTest : public QObject
{
    Q_OBJECT
    private slots:
        void persistImageFileDataTest();
};
#endif
