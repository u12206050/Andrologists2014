#ifndef FAKEFILTER_H
#define FAKEFILTER_H

#include "Filter.h"
#include "Fake.h"

class FakeFilter : public Filter, public Fake
{
    public:
        FakeFilter();
        ~FakeFilter();
        ImageData* filter(ImageData* image);
};

#endif // FAKEFILTER_H
