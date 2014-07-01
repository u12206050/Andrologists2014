#ifndef DATABASEPERSISTREQUEST_H
#define DATABASEPERSISTREQUEST_H
class DatabasePersistRequest
{
public:
    DatabasePersistRequest();
    string originalImageFilename;
    QDateTime timeStamp;
    vector<string> facesFilenames;


};
#endif // DATABASEPERSISTREQUEST_H
