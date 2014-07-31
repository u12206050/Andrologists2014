#ifndef PERSISTER_H
#define PERSISTER_H

#include "ImageData.h"

class Persister
{
	public:
	    virtual ~Persister();
	    virtual void persistImageData(ImageData* image) = 0;
};

#endif 
