#ifndef DATABASEPERSISTER_H
#define DATABASEPERSISTER_H

#include "DatabasePersistRequest.h"
#include "ErrorException.h"

#include <QtSql>

using namespace std;

class DatabasePersister
{
    public:
        DatabasePersister(QSqlDatabase database);
        ~DatabasePersister();
        void persistImageFileData(DatabasePersistRequest* request);

   private:
        QSqlDatabase database;
};

#endif // DATABASEPERSISTER_H
