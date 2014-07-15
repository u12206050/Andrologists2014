#ifndef DATABASEREADERTEST_H
#define DATABASEREADERTEST_H

#include <QtTest/QtTest>
#include "DatabaseReader.h"

class DatabaseReaderTest : public QObject
{
	Q_OBJECT
	private slots:
		void getAllFacesInRangeTest();
};

#endif // DATABASEREADERTEST_H
