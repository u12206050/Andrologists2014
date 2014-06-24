#include "FakePersister.h"

FakePersister::~FakePersister()
{
}

void FakePersister::persistImageData(ImageData* image)
{
    calledFlag = true;
    if (image == NULL)
    {
        throw "Invalid Image";
    }
}

bool FakePersister::getCalledFlag()
{
    return calledFlag;
}
