#ifndef DATABASEREADER_H
#define DATABASEREADER_H

#include "ErrorException.h"
#include "GetAllFacesInRangeResponse.h"
#include "GetFaceDetailsResponse.h"
#include <QtSql>

class DatabaseReader
{
	public:
        DatabaseReader(QSqlDatabase database);
		GetAllFacesInRangeResponse* getAllFacesInRange(QDateTime begin, QDateTime end);
        QString getImagePath(QString randomIdentifier);
        QString getOriginalImageFilename(int caseId);
        GetFaceDetailsResponse* getAllFaceFilenamesAndIds();

	private:
		QSqlDatabase database;
};

#endif // DATABASEREADER_H
