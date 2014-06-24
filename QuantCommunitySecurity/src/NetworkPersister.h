#if !defined(_NETWORKPERSISTER_H)
#define _NETWORKPERSISTER_H

#include "Persister.h"

class NetworkPersister : public Persister
{
public:
	~NetworkPersister();
	void persistImageData(ImageData* image);
};

#endif  //_NETWORKPERSISTER_H
