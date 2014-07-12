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

}
