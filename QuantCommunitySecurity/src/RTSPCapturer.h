#if !defined(_RTSPCAPTURER_H)
#define _RTSPCAPTURER_H

#include "Capturer.h"

class RTSPCapturer : public Capturer
{
    public:
        RTSPCapturer(QString& videoLocation);
        ~RTSPCapturer();
        ImageData* getNextImage();
    private:
        VideoCapture capturer;
};

#endif  //_RTSPCAPTURER_H
