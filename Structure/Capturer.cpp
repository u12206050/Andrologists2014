#include "Capturer.h"

Capturer::Capturer(String source)
{
	capturer = cvCaptureFromCAM(source); //Something like this
	if (!capturer)
	{
		//Throw some exception maybe
	}
}

Capturer::~Capturer()
{
	cvReleaseCapture(&capturer);
}

Mat Capturer::getNextFrame()
{
	return cvQueryFrame(capturer);
}
