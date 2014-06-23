#include "FakePersister.h"

FakePersister::~FakePersister()
{
}

void FakePersister::persistImageData(ImageData* image)
{
    if (image == NULL)
    {
        throw "Invalid Image";
    }
}
