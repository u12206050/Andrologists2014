#ifndef FAKEPERSISTER_H
#define FAKEPERSISTER_H

#include "Persister.h"

class FakePersister : public Persister
{
    public:
        ~FakePersister();
        persistImageData(ImageData* image);
};

#endif // FAKEPERSISTER_H
