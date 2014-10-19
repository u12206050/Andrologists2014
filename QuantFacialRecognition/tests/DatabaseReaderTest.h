#ifndef DATABASEREADERTEST_H
#define DATABASEREADERTEST_H

#include <QtTest/QtTest>
#include "DatabaseReader.h"

class DatabaseReaderTest : public QObject
{
	Q_OBJECT
	private slots:
		void getAllFacesInRangeTest();
		void getImagePath();
		void getOriginalImageFilename();
		void getAllFaceFilenamesAndIds();
};

#endif // DATABASEREADERTEST_H
