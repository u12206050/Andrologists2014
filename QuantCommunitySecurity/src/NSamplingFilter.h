#ifndef N_SAMPLING_FILTER_H
#define N_SAMPLING_FILTER_H

#include "Filter.h"

class NSamplingFilter : public Filter
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
