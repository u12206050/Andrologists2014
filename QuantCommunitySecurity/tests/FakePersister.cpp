#include "FakePersister.h"

FakePersister::FakePersister() : Fake()
{

}

FakePersister::~FakePersister()
{
}

void FakePersister::persistImageData(ImageData* image)
{
    numCalled++;
    if (image == NULL)
    {
        throw "Invalid Image";
    }
}
