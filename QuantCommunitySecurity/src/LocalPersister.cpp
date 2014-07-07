#include "LocalPersister.h"

LocalPersister::LocalPersister(QString& directoryPath, int id)
{
    this->directoryPath = directoryPath;
    this->id = id;
    /*if(access(directory, 0) == -1)
    {
        mkdir(directory);
    }*/
}

LocalPersister::~LocalPersister()
{

}

void LocalPersister::persistImageData(ImageData* image)
{
    if(!image->faces.empty())
    {
        QString baseFileName(directoryPath);

        QDateTime dateTime;
        int seconds = dateTime.currentMSecsSinceEpoch();

        QTextStream(&baseFileName) << "i_" << id << "_name_" << seconds;

        QString filename(baseFileName);
        QTextStream(&filename) << ".jpg";
        imwrite(filename.toStdString(), image->image);

        for (int i = 0; i < image->faces.size(); i++)
        {
            QString face(baseFileName);
            QTextStream(&face) << "_face_" << i << ".jpg";
            imwrite(face.toStdString(), image->faces[i]);
        }
    }

}
