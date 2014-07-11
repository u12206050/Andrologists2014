#include "DatabasePersisterTest.h"

void DatabasePersisterTest::persistImageFileDataTest()
{
    QString dbType("QPSQL");
    QString hostname("127.0.0.1");
    QString dbName("quant");
    QString username("zane");
    QString password("root");
    int port = 5432;

    DatabasePersistRequest* request =  new DatabasePersistRequest;
    request->originalImageFilename.fromStdString("testFile");
    request->timeStamp = 10;
    request->facesFilenames.push_back(QString("testFace1"));
    request->facesFilenames.push_back(QString("testFace2"));
    request->facesFilenames.push_back(QString("testFace3"));

    DatabasePersister dbPersister = DatabasePersister(dbType, hostname, dbName, username, password, port);
    dbPersister.persistImageFileData(request);//surround with try catch
}
