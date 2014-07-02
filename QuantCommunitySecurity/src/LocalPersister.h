#if !defined(_LOCALPERSISTER_H)
#define _LOCALPERSISTER_H

#include "Persister.h"

class LocalPersister : public Persister
{
private:
    char* directory;
public:
    LocalPersister(String dir);
	~LocalPersister();
	void persistImageData(ImageData* image);
};

#endif  //_LOCALPERSISTER_H
