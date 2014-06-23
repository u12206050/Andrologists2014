#if !defined(_PERSISTER_H)
#define _PERSISTER_H

#include "ImageData.h"

class Persister
{
    public:
        virtual ~Persister();
        virtual void persistImageData(ImageData* image) = 0;
};

#endif  //_PERSISTER_H
