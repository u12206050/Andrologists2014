#include "LocalPersister.h"

LocalPersister::~LocalPersister()
{

}

void LocalPersister::persistImageData(ImageData* image)
{

    char file_name[100];

    QDate cd = image->timestamp.date();
    QTime ct = image->timestamp.time();

    sprintf(file_name, "images/%02d%02d%04d-%02d%02d%02d(%d).jpg", cd.day(), cd.month(), cd.year(), ct.hour(), ct.minute(), ct.second(), ct.msec());

    //cout << file_name << endl;
    if(!image->faces.empty())
    {
        imwrite( file_name, image->image );
    }
}
