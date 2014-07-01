#ifndef WEBCAMCAPTURER_H
#define WEBCAMCAPTURER_H

#include "Capturer.h"

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
