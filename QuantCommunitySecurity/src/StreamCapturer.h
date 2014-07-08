#if !defined(_STREAMCAPTURER_H)
#define _STREAMCAPTURER_H

#include "Capturer.h"

class StreamCapturer : public Capturer
{
    public:
        StreamCapturer(QString& videoLocation);
        StreamCapturer(int deviceId);
        ~StreamCapturer();
        ImageData* getNextImage();

    private:
        VideoCapture capturer;
};

#endif  //_RTSPCAPTURER_H
