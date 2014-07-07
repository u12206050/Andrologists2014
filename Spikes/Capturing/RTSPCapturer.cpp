#include "RTSPCapturer.h"
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;

RTSPCapturer::RTSPCapturer(char* Url)
{

    capture = NULL;
    capture = cvCreateFileCapture(Url);  //Capture rtsp camera

    cout << capture << endl;
    IplImage* frame = cvQueryFrame(capture);
    Mat imgMat(frame);

    /*string filen(Url);
    cout << filen << endl;
    VideoCapture cap;
    cout << Url << endl;
    cap.open(filen);
    cout << cap.isOpened() << endl;
    cap.read(imgMat);
    cout << imgMat << endl;*/
    namedWindow("TEST", CV_WINDOW_AUTOSIZE);

    imshow("test", imgMat);

    /*if(capture == NULL)
    {
        throw Exception();
    }*/

    data = new ImageData();
    //cout << "here2" << endl;
}

RTSPCapturer::~RTSPCapturer()
{
    cvReleaseCapture(&capture);
    delete data;
}

ImageData* RTSPCapturer::getNextImage()
{
    data->faces.clear();

    IplImage* frame = cvQueryFrame(capture);
    if (frame == NULL)
        return NULL;

    Mat imgMat(frame);
    data->image = imgMat;

    //QDate cd = QDate::currentDate();
    //QTime ct = QTime::currentTime();

    //data->timestamp.setDate(cd);
    //data->timestamp.setTime(ct);

    return data;
}
