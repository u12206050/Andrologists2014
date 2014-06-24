#ifndef FAKEFILTER_H
#define FAKEFILTER_H

#include "Filter.h"

class FakeFilter : public Filter
{
    public:
        FakeFilter();
        ~FakeFilter();
        ImageData* filter(ImageData* image);
        bool getCalledFlag();

    private:
        bool calledFlag;
};

#endif // FAKEFILTER_H
