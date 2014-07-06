#include "ImageCapturer.h"

ImageCapturer::ImageCapturer(String loc)
{
    directory = new char[100];
    strcpy(directory, loc.c_str());
    if(access(directory, 0) == -1)
    {
        throw Exception();
    }
    dir = opendir(directory);     // open current directory
    data = NULL;
}

ImageCapturer::~ImageCapturer()
{
    delete directory;
    delete data;

    closedir(dir);
}

ImageData* ImageCapturer::getNextImage()
{
    if(pdir = readdir(dir))
    {
        //cout << pdir->d_name << " - ";

        // Load image

        char file[100];
        sprintf(file, "%s/%s", directory, pdir->d_name);
        IplImage* frame = cvLoadImage(file);

        //cout << frame << endl;
        if(frame != 0)
        {
            Mat imgMat(frame);

            data = new ImageData();
            data->image = imgMat;

            QDate cd = QDate::currentDate();
            QTime ct = QTime::currentTime();

            data->timestamp.setDate(cd);
            data->timestamp.setTime(ct);

            //Convert Mat to IplImage
            //IplImage copy = data->image;
            //IplImage* new_image = &copy;
        }
        remove(file);
    }

    return data;
}


