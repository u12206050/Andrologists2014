#if !defined(_RTSPCAPTURER_H)
#define _RTSPCAPTURER_H

#include "Capturer.h"

class RTSPCapturer : public Capturer
{
public:
	~RTSPCapturer();
	ImageData* getNextImage();
};

#endif  //_RTSPCAPTURER_H
