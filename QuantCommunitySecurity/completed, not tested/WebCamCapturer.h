#ifndef WEBCAMCAPTURER_H
#define WEBCAMCAPTURER_H

#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>

#include "Capturer.h"
#include "ImageData.h"

class WebCamCapturer : public Capturer
{
private:
    CvCapture* capture;
    ImageData* data;
public:
    WebCamCapturer();
    ~WebCamCapturer();
    ImageData* getNextImage();
};

#endif // WEBCAMCAPTURER_H
