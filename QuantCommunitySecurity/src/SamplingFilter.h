#if !defined(_SAMPLINGFILTER_H)
#define _SAMPLINGFILTER_H

#include "Filter.h"

class SamplingFilter : public Filter
{
    public:
        ~SamplingFilter();
        virtual ImageData* filter(ImageData* image);
};

#endif  //_SAMPLINGFILTER_H
