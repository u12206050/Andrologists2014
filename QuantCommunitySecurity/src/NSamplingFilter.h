#if !defined(_NSAMPLINGFILTER_H)
#define _NSAMPLINGFILTER_H

#include "SamplingFilter.h"

class NSamplingFilter : public SamplingFilter
{
    public:
        NSamplingFilter(int n);
        ~NSamplingFilter();
        ImageData* filter(ImageData* image);

    private:
        int n;
        int counter;
};

#endif  //_NSAMPLINGFILTER_H
