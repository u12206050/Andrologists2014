#include "WebCamCapturer.h"

WebCamCapturer::WebCamCapturer()
{

    capture = cvCaptureFromCAM(CV_CAP_ANY);  //Capture using any camera connected to your system

    if(capture == NULL)
    {
        throw Exception();
    }

    data = new ImageData();
}

WebCamCapturer::~WebCamCapturer()
{
    cvReleaseCapture(&capture);
    delete data;
}

ImageData* WebCamCapturer::getNextImage()
{
    IplImage* frame = cvQueryFrame(capture); //Create image frames from capture
    if (frame == NULL)
        return NULL;
    Mat imgMat(frame);
    data->image = imgMat;

    //Convert Mat to IplImage
    //IplImage copy = data->image;
    //IplImage* new_image = &copy;

    return data;
}

