#ifndef STREAM_CAPTURER_H
#define STREAM_CAPTURER_H

#include "Capturer.h"
#include "ErrorException.h"

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

#endif
