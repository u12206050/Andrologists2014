#if !defined(_LOCALPERSISTER_H)
#define _LOCALPERSISTER_H

#include "Persister.h"

class LocalPersister : public Persister
{
public:
	~LocalPersister();
	void persistImageData(ImageData* image);
	void persistImageData(ImageData* image);
};

#endif  //_LOCALPERSISTER_H
