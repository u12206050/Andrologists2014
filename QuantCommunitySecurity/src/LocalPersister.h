#if !defined(_LOCALPERSISTER_H)
#define _LOCALPERSISTER_H

#include "Persister.h"
#include <QTextStream>
#include <sys/stat.h>

class LocalPersister : public Persister
{
    public:
        LocalPersister(QString& directoryPath, int id);
        ~LocalPersister();
        void persistImageData(ImageData* image);

    private:
        QString directoryPath;
        int id;
};

#endif  //_LOCALPERSISTER_H
