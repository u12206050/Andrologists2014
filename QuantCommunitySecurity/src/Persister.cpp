#include "Persister.h"

Persister::~Persister()
{

}

void Persister::setDatabasePersister(DatabasePersister* databasePersister)
{
    this->databasePersister = databasePersister;
}
