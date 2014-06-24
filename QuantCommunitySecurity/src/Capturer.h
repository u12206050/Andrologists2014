#if !defined(_CAPTURER_H)
#define _CAPTURER_H

#include "ImageData.h"

class Capturer
{
    public:
        virtual ~Capturer();
        virtual ImageData* getNextImage() = 0;
};

#endif  //_CAPTURER_H
