#if !defined(_CAPTURER_H)
#define _CAPTURER_H

#include "ImageData.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QTime>
#include <QDate>
#include <sys/types.h>  // For stat().
#include <sys/stat.h>   // For stat().
#include <string.h>

#include "dirent.h"

class Capturer
{
private:
    CvCapture* capture;
    ImageData* data;
public:
    virtual ~Capturer();
    virtual ImageData* getNextImage() = 0;
};

#endif  //_CAPTURER_H
