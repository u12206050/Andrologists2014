#ifndef DATABASEPERSISTREQUEST_H
#define DATABASEPERSISTREQUEST_H

#include <QDateTime>

using namespace std;

class DatabasePersistRequest
{
    public:
        QString originalImageFilename;
        qint64 timeStamp;
        vector<QString> facesFilenames;
};

#endif // DATABASEPERSISTREQUEST_H
