#if !defined(_RTSPCAPTURER_H)
#define _RTSPCAPTURER_H

#include "Capturer.h"

class RTSPCapturer : public Capturer
{
private:
    CvCapture* capture;
    ImageData* data;
public:
    RTSPCapturer(char* url);
	~RTSPCapturer();
	ImageData* getNextImage();
};

#endif  //_RTSPCAPTURER_H
