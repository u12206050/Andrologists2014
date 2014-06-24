#include "FakeCapturer.h"

FakeCapturer::FakeCapturer(ImageData image)
{
    this->image = image;
}

FakeCapturer::~FakeCapturer()
{
    delete image;
}

ImageData* FakeCapturer::getNextImage()
{
    calledFlag = true;
    return image;
}

bool FakeCapturer::getCalledFlag()
{
    return calledFlag;
}
