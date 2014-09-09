#include "DatabaseReader.h"

DatabaseReader::DatabaseReader(QSqlDatabase database)
{
    this->database = database;
}

GetAllFacesInRangeResponse* DatabaseReader::getAllFacesInRange(QDateTime begin, QDateTime end)
{
	if (database.open())
	{
		GetAllFacesInRangeResponse* response = new GetAllFacesInRangeResponse;

		qint64 beginTime = begin.toMSecsSinceEpoch();
		qint64 endTime = end.toMSecsSinceEpoch();

		QSqlQuery query;
		query.prepare("SELECT images.timestamp, faces.filename "
					  "FROM images, faces "
					  "WHERE images.id=faces.image_id AND images.timestamp BETWEEN :begin AND :end");
		query.bindValue(":begin", beginTime);
		query.bindValue(":end", endTime);

		if(!query.exec())
		{
			QString error("getting faces data.");
			throw ErrorException(error, 0);
		}

		while (query.next())
		{
			qint64 mSeconds = query.value(0).toLongLong();
			QDateTime timestamp;
			timestamp = timestamp.fromMSecsSinceEpoch(mSeconds);
			QString filename = query.value(1).toString();
			response->timestamps.push_back(timestamp);
			response->facesToCompareWith.push_back(filename);
		}

		return response;
	}
	else
	{
		QString error("database closed.");
		throw ErrorException(error, 1);
	}
}

QString DatabaseReader::getImagePath(QString randomIdentifier)
{
    if (database.open())
    {
        QSqlQuery query;
        query.prepare("SELECT images.filename "
                      "FROM images"
                      "WHERE images.id=faces.image_id AND caseResults.randomIdentifier='randomIdentifier'");

        if(!query.exec())
        {
            QString error("getting image path.");
            throw ErrorException(error, 0);
        }

        QString filename;
        while (query.next())
        {
            filename = query.value(0).toString();
        }

        return filename;
    }
    else
    {
        QString error("database closed.");
        throw ErrorException(error, 1);
    }

	//Select ImageId FROM CaseResults WHERE randomIdentifier = randomIdentifier
    //Something like this
}

QString DatabaseReader::getOriginalImageFilename(int caseId)
{
    if (database.open())
    {
        QSqlQuery query;
        query.prepare("SELECT images.filename "
                      "FROM cases, images"
                      "WHERE images.id = cases.image_id AND cases.id = :caseId");
        query.bindValue(":caseId", caseId);

        if(!query.exec())
        {
            QString error("getting image path.");
            throw ErrorException(error, 0);
        }

        QString filename = query.value(0).toString();

        return filename;
    }
    else
    {
        QString error("database closed.");
        throw ErrorException(error, 1);
    }
}

GetFaceDetailsResponse* DatabaseReader::getAllFaceFilenamesAndIds()
{
    if (database.open())
    {
        GetFaceDetailsResponse* response = new GetFaceDetailsResponse;
        vector<int> ids;
        vector<QString> faceNames;
        QSqlQuery query;
        query.prepare("SELECT faces.filename, faces.id"
                      "FROM faces");

        if(!query.exec())
        {
            QString error("getting face filenames.");
            throw ErrorException(error, 0);
        }

        while (query.next())
        {
            faceNames.push_back(query.value(0).toString());
            ids.push_back(query.value(1).toInt());
        }

        response->faceFilnames = faceNames;
        response->ids = ids;

        return response;
    }
    else
    {
        QString error("database closed.");
        throw ErrorException(error, 1);
    }
}
