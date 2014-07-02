#include "ImageCapturer.h"

ImageCapturer::ImageCapturer(String dir)
{
    directory = new char[100];
    strcpy(directory, dir.c_str());
    if(access(directory, 0) == -1)
    {
        throw Exception();
    }

    data = new ImageData();
}

ImageCapturer::~ImageCapturer()
{
    delete directory;
    delete data;
}

ImageData* ImageCapturer::getNextImage()
{
    struct _finddata_t c_file;
    long hFile;
    char imageFileType[] = "jpg";
    char file[100];

    sprintf(file,"%s/*.%s", directory, imageFileType);
    hFile = _findfirst( file, &c_file );
    /*Check to make sure that there are files in directory*/
    if( hFile != -1L )
    {
        //cout << "Listing of files:\n" ;
        // Loop through all images of imageFileType

        char tmp[100];
        sprintf(tmp,"%s/%s", directory, c_file.name);

        // Load image
        IplImage* frame = cvLoadImage(tmp);

        Mat imgMat(frame);
        data->image = imgMat;

        QDate cd = QDate::currentDate();
        QTime ct = QTime::currentTime();

        data->timestamp.setDate(cd);
        data->timestamp.setTime(ct);

        remove(tmp);
        //Convert Mat to IplImage
        //IplImage copy = data->image;
        //IplImage* new_image = &copy;

    }
    else
    {
        data = NULL;
    }
    return data;
}


