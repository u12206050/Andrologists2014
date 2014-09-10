#ifndef FAKEDATABASEPERSISTER_H
#define FAKEDATABASEPERSISTER_H

#include "DatabasePersister.h"

class FakeDatabasePersister : public DatabasePersister
{
    public:
        FakeDatabasePersister();
        virtual void persistImageFileData(DatabasePersistRequest* request);
};

#endif // FAKEDATABASEPERSISTER_H
