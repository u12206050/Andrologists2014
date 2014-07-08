#ifndef DATABASEPERSISTREQUEST_H
#define DATABASEPERSISTREQUEST_H
#include <QDateTime>
#include <iostream>
#include "string.h"
using namespace std;
class DatabasePersistRequest
{
public:
    DatabasePersistRequest();
    DatabasePersistRequest(string filename, QDateTime timestamp);
    string originalImageFilename;
    QDateTime timeStamp;
    vector<string> facesFilenames;



};
#endif // DATABASEPERSISTREQUEST_H
