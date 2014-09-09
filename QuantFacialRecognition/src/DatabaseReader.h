#ifndef DATABASEREADER_H
#define DATABASEREADER_H

#include "ErrorException.h"
#include "GetAllFacesInRangeResponse.h"
#include "GetFaceDetailsResponse.h"
#include <QtSql>
#include <vector>

class DatabaseReader
{
	public:
		DatabaseReader(QString& databaseType, QString& hostname, QString& databaseName, QString& username, QString& password, int port);
		GetAllFacesInRangeResponse* getAllFacesInRange(QDateTime begin, QDateTime end);
        QString getImagePath(QString randomIdentifier);
        QString getOriginalImageFilename(int caseId);
        GetFaceDetailsResponse* getAllFaceFilenamesAndIds();

	private:
		QSqlDatabase database;
};

#endif // DATABASEREADER_H
