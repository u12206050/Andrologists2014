#ifndef PERSISTER_H
#define PERSISTER_H

#include "ImageData.h"
#include "DatabasePersister.h"

class Persister
{
	public:
	    virtual ~Persister();
	    virtual void persistImageData(ImageData* image) = 0;
        void setDatabasePersister(DatabasePersister* databasePersister);
    protected:
        DatabasePersister* databasePersister;

};

#endif 
