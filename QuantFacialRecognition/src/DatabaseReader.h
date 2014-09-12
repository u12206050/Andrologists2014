#ifndef DATABASEREADER_H
#define DATABASEREADER_H

#include "ErrorException.h"
#include "GetAllFacesInRangeResponse.h"
#include "GetFaceDetailsResponse.h"
#include "DatabaseConnection.h"
#include <QtSql>

class DatabaseReader
{
	public:
        DatabaseReader(DatabaseConnection* databaseConnection);
		GetAllFacesInRangeResponse* getAllFacesInRange(QDateTime begin, QDateTime end);
        QString getImagePath(QString randomIdentifier, int type);
        QString getOriginalImageFilename(int caseId);
        GetFaceDetailsResponse* getAllFaceFilenamesAndIds();

	private:
        DatabaseConnection* databaseConnection;
};

#endif // DATABASEREADER_H
