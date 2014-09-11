#ifndef DATABASEPERSISTER_H
#define DATABASEPERSISTER_H

#include "DatabasePersistRequest.h"
#include "ErrorException.h"
#include "DatabaseConnection.h"

using namespace std;

class DatabasePersister
{
    public:
        DatabasePersister();
        DatabasePersister(DatabaseConnection* databaseConnection);
        ~DatabasePersister();
        virtual void persistImageFileData(DatabasePersistRequest* request);

   private:
        DatabaseConnection* databaseConnection;
};

#endif // DATABASEPERSISTER_H
