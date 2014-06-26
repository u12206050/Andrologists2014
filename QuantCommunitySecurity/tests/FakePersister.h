#ifndef FAKEPERSISTER_H
#define FAKEPERSISTER_H

#include "Persister.h"
#include "Fake.h"

class FakePersister : public Persister, public Fake
{
    public:
        FakePersister();
        ~FakePersister();
        void persistImageData(ImageData* image);
};

#endif // FAKEPERSISTER_H
