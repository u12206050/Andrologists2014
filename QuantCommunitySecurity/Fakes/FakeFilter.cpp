#include "FakeFilter.h"

FakeFilter::~FakeFilter()
{
}

ImageData* FakeFilter::filter(ImageData* image)
{
    calledFlag = true;
    return image;
}

bool FakeFilter::getCalledFlag()
{
    return calledFlag;
}
