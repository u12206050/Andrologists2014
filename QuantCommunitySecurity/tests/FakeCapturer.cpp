#include "FakeCapturer.h"

FakeCapturer::FakeCapturer(ImageData* image) : Fake()
{
    this->image = image;
}

FakeCapturer::~FakeCapturer()
{
    delete image;
}

ImageData* FakeCapturer::getNextImage()
{
    numCalled++;
    return image;
}


