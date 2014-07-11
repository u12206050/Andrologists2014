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
        query.prepare("INSERT INTO Images (filename, timestamp) VALUES (:filename, :timestamp)");
        query.bindValue(":filename", request->originalImageFilename);
        query.bindValue(":time", request->timeStamp);
        if(!query.exec())
        {
            //throw some exception cound not insert image
        }

        query.clear();
        query.prepare("SELECT id FROM Images WHERE filename = :filename");
        query.bindValue(":filename", request->originalImageFilename);
        if(!query.exec())
        {
            //throw some exception could not insert images
        }

        query.first();
        qint64 imageId = query.value(0).toLongLong();

        for (unsigned int i = 0; i < request->facesFilenames.size(); i++)
        {
            query.clear();
            query.prepare("INSERT INTO FaceImages (filename, imageId) VALUES (:filename, :imageId)");
            query.bindValue(":filename", request->facesFilenames[i]);
            query.bindValue(":imageId", imageId);
            if(!query.exec())
            {
                //throw some exception could not insert face i
            }
        }
        database.close();
    }

    //throw some exception closed database
}
