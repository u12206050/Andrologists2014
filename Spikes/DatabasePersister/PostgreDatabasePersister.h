#ifndef POSTGREDATABASEPERSISTER_H
#define POSTGREDATABASEPERSISTER_H
#include "DatabasePersister.h"

class PostgreDatabasePersister : public DatabasePersister
{
public:
    PostgreDatabasePersister();
    ~PostgreDatabasePersister();
    void persistImageFileData(DatabasePersistRequest request);
    void viewDatabase();
    void insertIntoDatabase(string filename, QDateTime timestamp);
};
#endif // POSTGREDATABASEPERSISTER_H
