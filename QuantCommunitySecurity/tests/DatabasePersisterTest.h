#ifndef DATABASEPERSISTERTEST_H
#define DATABASEPERSISTERTEST_H

#include <QtTest/QtTest>

#include "DatabasePersister.h"

/*
    #include <QtDebug>
    #include "DatabasePersistRequest.h"
    #include "DatabasePersister.h"
    #include "PostgreDatabasePersister.h"
    #include <QDateTime>
    using namespace std;
*/

class DatabasePersisterTest : public QObject
{
    Q_OBJECT
    private slots:
        void persistImageFileDataTest();
};
#endif // DATABASEPERSISTERTEST_H
