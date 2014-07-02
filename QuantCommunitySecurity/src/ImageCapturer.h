#ifndef IMAGECAPTURER_H
#define IMAGECAPTURER_H

#include "Capturer.h"

class ImageCapturer : public Capturer
{
private:
    CvCapture* capture;
    char* directory;
    ImageData* data;
public:
    ImageCapturer(String dir);
    ~ImageCapturer();
    ImageData* getNextImage();
};

#endif // IMAGECAPTURER_H
