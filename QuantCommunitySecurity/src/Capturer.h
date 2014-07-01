#if !defined(_CAPTURER_H)
#define _CAPTURER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QTime>
#include <QDate>
#include <string.h>

#include "ImageData.h"

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
