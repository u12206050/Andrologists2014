#ifndef CAPTURER_H
#define CAPTURER_H

#include "ImageData.h"

class Capturer
{
	public:
	    virtual ~Capturer();
	    virtual ImageData* getNextImage() = 0;
};

#endif
