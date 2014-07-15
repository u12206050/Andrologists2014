#include "DatabaseReader.h"

DatabaseReader::DatabaseReader(QString& databaseType, QString& hostname, QString& databaseName, QString& username, QString& password, int port)
{
	database = QSqlDatabase::addDatabase(databaseType);
	database.setHostName(hostname);
	database.setDatabaseName(databaseName);
	database.setUserName(username);
	database.setPassword(password);
	database.setPort(port);
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
