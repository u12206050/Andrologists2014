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
    return image;
}
