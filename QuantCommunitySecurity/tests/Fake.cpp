#include "Fake.h"

Fake::Fake()
{
    numCalled = 0;
}

int Fake::getNumCalled()
{
    return numCalled;
}

void Fake::reset()
{
    numCalled = 0;
}
