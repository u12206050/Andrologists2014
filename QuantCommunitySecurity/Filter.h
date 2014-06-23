#if !defined(_FILTER_H)
#define _FILTER_H

#include "ImageData.h"


class Filter
{
    public:
        virtual ~Filter();
        virtual ImageData* filter(ImageData* image) = 0;
};

#endif  //_FILTER_H
