#ifndef DATABASEPERSISTER_H
#define DATABASEPERSISTER_H
#include "DatabasePersistRequest.h"
class DatabasePersister
{
public:
    DatabasePersister();
    ~DatabasePersister();
    virtual bool persistImageFileData(DatabasePersistRequest request);
};
#endif // DATABASEPERSISTER_H
