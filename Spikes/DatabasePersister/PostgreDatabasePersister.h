#ifndef POSTGREDATABASEPERSISTER_H
#define POSTGREDATABASEPERSISTER_H
#include "DatabasePersister.h"
class PostgreDatabasePersister : public DatabasePersister
{
public:
    ~PostgreDatabasePersister();
    void persistImageFileData(DatabasePersistRequest request);
};
#endif // POSTGREDATABASEPERSISTER_H
