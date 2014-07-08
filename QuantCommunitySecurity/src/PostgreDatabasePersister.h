#ifndef POSTGREDATABASEPERSISTER_H
#define POSTGREDATABASEPERSISTER_H
#include "DatabasePersister.h"

class PostgreDatabasePersister : public DatabasePersister
{
public:
    PostgreDatabasePersister();
    ~PostgreDatabasePersister();
    bool persistImageFileData(DatabasePersistRequest request);
    void viewDatabase();
    bool insertIntoDatabase(string filename, QDateTime timestamp);
    string viewLastFilenameInserted();

};
#endif // POSTGREDATABASEPERSISTER_H
