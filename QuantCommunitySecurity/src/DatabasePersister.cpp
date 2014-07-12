#include "DatabasePersister.h"

DatabasePersister::DatabasePersister(QString& databaseType, QString& hostname, QString& databaseName, QString& username, QString& password, int port)
{
    database = QSqlDatabase::addDatabase(databaseType);
    database.setHostName(hostname);
    database.setDatabaseName(databaseName);
    database.setUserName(username);
    database.setPassword(password);
    database.setPort(port);
}

DatabasePersister::~DatabasePersister()
{

}

void DatabasePersister::persistImageFileData(DatabasePersistRequest* request)
{
    if (database.open())
    {
        QSqlQuery query;
        query.prepare("INSERT INTO test.Images (filename, timestamp) VALUES (:filename, :timestamp)");
        query.bindValue(":filename", request->originalImageFilename);
        query.bindValue(":timestamp", request->timeStamp);
        if(!query.exec())
        {
            QString error(query.lastError().text());
            throw ErrorException(error, 0);
        }

        query.clear();
        query.prepare("SELECT id FROM test.Images WHERE filename = :filename");
        query.bindValue(":filename", request->originalImageFilename);
        if(!query.exec())
        {
            QString error("inserting image data.");
            throw ErrorException(error, 1);
        }

        query.first();
        qint64 imageId = query.value(0).toLongLong();

        for (unsigned int i = 0; i < request->facesFilenames.size(); i++)
        {
            query.clear();
            query.prepare("INSERT INTO test.FaceImages (filename, imageId) VALUES (:filename, :imageId)");
            query.bindValue(":filename", request->facesFilenames[i]);
            query.bindValue(":imageId", imageId);
            if(!query.exec())
            {
                QString error("inserting face data.");
                throw ErrorException(error, 2);
            }
        }
        database.close();
    }

    QString error("database closed.");
    throw ErrorException(error, 3);
}
