#ifndef DATABASEREADER_H
#define DATABASEREADER_H

#include "ErrorException.h"
#include "GetAllFacesInRangeResponse.h"
#include <QtSql>

class DatabaseReader
{
	public:
		DatabaseReader(QString& databaseType, QString& hostname, QString& databaseName, QString& username, QString& password, int port);
		GetAllFacesInRangeResponse* getAllFacesInRange(QDateTime begin, QDateTime end);

	private:
		QSqlDatabase database;
};

#endif // DATABASEREADER_H
