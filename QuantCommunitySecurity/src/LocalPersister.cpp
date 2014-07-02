#include "LocalPersister.h"

LocalPersister::LocalPersister(String dir)
{
    directory = new char[100];
    strcpy(directory, dir.c_str());
    if(access(directory, 0) == -1)
    {
        mkdir(directory);
    }
}

LocalPersister::~LocalPersister()
{
    delete directory;
}

void LocalPersister::persistImageData(ImageData* image)
{
    char file_name[50];

    QDate cd = image->timestamp.date();
    QTime ct = image->timestamp.time();

    sprintf(file_name, "/%02d%02d%04d-%02d%02d%02d(%d).jpg", cd.day(), cd.month(), cd.year(), ct.hour(), ct.minute(), ct.second(), ct.msec());

    char tmp[100];
    strcpy(tmp, directory);
    strcat(tmp, file_name);

    if(!image->faces.empty())
    {
        //cout << tmp << endl;
        imwrite( tmp, image->image );
    }
}
