#include "FakeFilter.h"

FakeFilter::FakeFilter() : Fake()
{

}

FakeFilter::~FakeFilter()
{
}

ImageData* FakeFilter::filter(ImageData* image)
{
    numCalled++;
    return image;
}
