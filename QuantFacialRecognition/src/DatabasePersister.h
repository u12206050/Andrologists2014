#ifndef DATABASEPERSISTER_H
#define DATABASEPERSISTER_H

#include "DatabasePersistRequest.h"
#include "ErrorException.h"
#include <cstdlib>
#include <ctime>

#include <QtSql>

using namespace std;

class DatabasePersister
{
    public:
        DatabasePersister(QString& databaseType, QString& hostname, QString& databaseName, QString& username, QString& password, int port);
        ~DatabasePersister();
        void persistImageFileData(DatabasePersistRequest* request);
        void updateCaseStatus(int caseId, int faceId, double percentageMatch);

   private:
        QSqlDatabase database;
};

#endif // DATABASEPERSISTER_H
