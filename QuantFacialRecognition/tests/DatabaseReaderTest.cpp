#include "DatabaseReaderTest.h"

void DatabaseReaderTest::getAllFacesInRangeTest()
{
	QString dbType("QPSQL");
	QString hostname("192.168.0.6");
	QString dbName("quantTest");
	QString username("postgres");
	QString password("root");
	int port = 5432;

	DatabaseConnection* dbConnection= new DatabaseConnection(dbType, hostname, dbName, username, password, port);

	DatabaseReader reader(dbConnection);
	QDateTime start;
	start = start.fromMSecsSinceEpoch(0);
	QDateTime end;
	end = end.fromMSecsSinceEpoch(9);
	GetAllFacesInRangeResponse* response = reader.getAllFacesInRange(start, end);
	QVERIFY(response->facesToCompareWith.size() == 30);
}

void DatabaseReaderTest::getImagePath()
{
	QString dbType("QPSQL");
	QString hostname("192.168.0.6");
	QString dbName("quantTest");
	QString username("postgres");
	QString password("root");
	int port = 5432;

	DatabaseConnection* dbConnection= new DatabaseConnection(dbType, hostname, dbName, username, password, port);

	DatabaseReader reader(dbConnection);
	QString face = reader.getImagePath(QString("bob"), 1);
	QVERIFY(face.toStdString() == "/testFace2");

	QString image = reader.getImagePath(QString("bob"), 0);
	QVERIFY(image.toStdString() == "/testFile");
}

void DatabaseReaderTest::getOriginalImageFilename()
{
	QString dbType("QPSQL");
	QString hostname("192.168.0.6");
	QString dbName("quantTest");
	QString username("postgres");
	QString password("root");
	int port = 5432;

	DatabaseConnection* dbConnection= new DatabaseConnection(dbType, hostname, dbName, username, password, port);

	DatabaseReader reader(dbConnection);
	QString image = reader.getOriginalImageFilename(1);
	QVERIFY(image.toStdString() == "testFile");
}

void DatabaseReaderTest::getAllFaceFilenamesAndIds()
{
	QString dbType("QPSQL");
	QString hostname("192.168.0.6");
	QString dbName("quantTest");
	QString username("postgres");
	QString password("root");
	int port = 5432;

	DatabaseConnection* dbConnection= new DatabaseConnection(dbType, hostname, dbName, username, password, port);

	DatabaseReader reader(dbConnection);
	GetFaceDetailsResponse* response = reader.getAllFaceFilenamesAndIds();
	QVERIFY(response->faceFilnames.size() == 33);
}
