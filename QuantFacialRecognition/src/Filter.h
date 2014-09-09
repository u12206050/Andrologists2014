#ifndef FILTER_H
#define FILTER_H

#include "ImageData.h"

class Filter
{
    public:
        virtual ~Filter();
        virtual ImageData* filter(ImageData* image) = 0;
};


#endif
