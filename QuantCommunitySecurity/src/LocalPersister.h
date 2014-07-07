#if !defined(_LOCALPERSISTER_H)
#define _LOCALPERSISTER_H

#include "Persister.h"

class LocalPersister : public Persister
{
    public:
        LocalPersister(char* directory);
        ~LocalPersister();
        void persistImageData(ImageData* image);

    private:
        char* directory;
};

#endif  //_LOCALPERSISTER_H
