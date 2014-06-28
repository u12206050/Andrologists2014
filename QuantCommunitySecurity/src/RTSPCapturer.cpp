#include "RTSPCapturer.h"

RTSPCapturer::RTSPCapturer(char* Url)
{
    capture = cvCreateFileCapture(Url);  //Capture rtsp camera

    if(capture == NULL)
    {
        throw Exception();
    }

    data = new ImageData();
}

RTSPCapturer::~RTSPCapturer()
{
    cvReleaseCapture(&capture);
    delete data;
}

ImageData* RTSPCapturer::getNextImage()
{
    IplImage* frame = cvQueryFrame(capture);
    if (frame == NULL)
        return NULL;

    Mat imgMat(frame);
    data->image = imgMat;

    return data;
}
