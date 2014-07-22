#include "DatabasePersisterTest.h"

void DatabasePersisterTest::persistImageFileDataTest()
{
    QString dbType("QPSQL");
    QString hostname("127.0.0.1");
    QString dbName("postgres");
    QString username("postgres");
    QString password("root");
    int port = 5432;

    DatabasePersistRequest* request =  new DatabasePersistRequest;
	request->originalImageFilename = "testFile";
    request->timeStamp = 10;
    request->facesFilenames.push_back(QString("testFace1"));
    request->facesFilenames.push_back(QString("testFace2"));
    request->facesFilenames.push_back(QString("testFace3"));

    DatabasePersister dbPersister = DatabasePersister(dbType, hostname, dbName, username, password, port);
    try
    {
        dbPersister.persistImageFileData(request);
    }
    catch (ErrorException e)
    {
        switch(e.getErrorCode())
        {
            case 0:
                QVERIFY(false);
                break;
            case 1:
                QVERIFY(false);
                break;
            case 2:
                QVERIFY(false);
                break;
            case 3:
                QVERIFY(false);
            default:
                QVERIFY(false);
        }
    }
}
