#ifndef FAKEPERSISTER_H
#define FAKEPERSISTER_H

#include "Persister.h"

class FakePersister : public Persister
{
    public:
        FakePersister();
        ~FakePersister();
        void persistImageData(ImageData* image);
        bool getCalledFlag();

    private:
        bool calledFlag;
};

#endif // FAKEPERSISTER_H
