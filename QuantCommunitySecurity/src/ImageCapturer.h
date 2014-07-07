#ifndef IMAGECAPTURER_H
#define IMAGECAPTURER_H

#include "Capturer.h"

class ImageCapturer : public Capturer
{
private:
    DIR*     dir;
    dirent*  pdir;
    CvCapture* capture;
    char* directory;
    ImageData* data;
public:
    ImageCapturer(String loc);
    ~ImageCapturer();
    ImageData* getNextImage();
};

#endif // IMAGECAPTURER_H
