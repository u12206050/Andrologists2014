#include "LocalPersister.h"

LocalPersister::LocalPersister(QString &directoryPath, int id)
{
    this->directoryPath = directoryPath;
    this->id = id;
    mkdir(directoryPath.toStdString().c_str(), 0777);
}

LocalPersister::LocalPersister(QString& directoryPath, int id, DatabasePersister* databasePresister)
{
    this->directoryPath = directoryPath;
    this->id = id;
    setDatabasePersister(databasePresister);
    mkdir(directoryPath.toStdString().c_str(), 0777);
}

LocalPersister::~LocalPersister()
{

}

void LocalPersister::persistImageData(ImageData* image)
{
    if(!image->faces.empty())
    {
        QString baseFileName(directoryPath);

        QTextStream(&baseFileName) << "i_" << id << "_name_" << image->timestamp;

        QString filename(baseFileName);
        QTextStream(&filename) << ".jpg";
        imwrite(filename.toStdString(), image->image);

        DatabasePersistRequest* request = new DatabasePersistRequest;
        request->originalImageFilename = filename;
        request->timeStamp = image->timestamp;

        for (unsigned int i = 0; i < image->faces.size(); i++)
        {
            QString face(baseFileName);
            QTextStream(&face) << "_face_" << i << ".jpg";
            imwrite(face.toStdString(), image->faces[i]);
            request->facesFilenames.push_back(face);
        }

        databasePersister->persistImageFileData(request);
    }

}
