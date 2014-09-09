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
		query.prepare("INSERT INTO images (filename, timestamp) VALUES (:filename, :timestamp)");
		query.bindValue(":filename", request->originalImageFilename);
		query.bindValue(":timestamp", request->timeStamp);
        if(!query.exec())
        {
			QString error("inserting image data.");
			throw ErrorException(error, 0);
        }

        query.clear();
		query.prepare("SELECT id FROM images WHERE filename = :filename");
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
			query.prepare("INSERT INTO faces (filename, image_id) VALUES (:filename, :imageId)");
            query.bindValue(":filename", request->facesFilenames[i]);
            query.bindValue(":imageId", imageId);
            if(!query.exec())
            {
                QString error("inserting face data.");
				throw ErrorException(error, 2);
            }
        }
    }
	else
	{
		QString error("database closed.");
		throw ErrorException(error, 3);
    }
}

void DatabasePersister::updateCaseStatus(int caseId, int faceId, double percentageMatch)
{
    string randomIdentifier = "";

    srand (time(NULL));
    for (int i = 0; i < 10; i++)
    {
        char c;
        int j = rand() % 4;
        if (j == 0)
        {
            c = (rand() % 10) + 48;
        }
        else if (j == 1)
        {
            c = (rand() % 26) + 65;
        }
        else
        {
            c = (rand() % 26) + 97;
        }
        randomIdentifier += c;
    }

    randomIdentifier += faceId;

    if (database.open())
    {
        QSqlQuery query;
        query.prepare("INSERT INTO case_results "
                      "(face_id, case_id, percentage_match, random_identifier) "
                      "VALUES (:faceId, :caseId, :percentageMatch, :randomIdentifier)");
        query.bindValue(":faceId", faceId);
        query.bindValue(":caseId", caseId);
        query.bindValue(":pecentageMatch", percentageMatch);
        query.bindValue(":randomIdentifier", randomIdentifier);
        if(!query.exec())
        {
            QString error("inserting case result.");
            throw ErrorException(error, 0);
        }
    }
    else
    {
        QString error("database closed.");
        throw ErrorException(error, 3);
    }
}
