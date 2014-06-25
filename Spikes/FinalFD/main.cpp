#include "FaceDetectFilter.h"
#include "ImageData.h"

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

char key;

int main()
{

    FaceDetectFilter detect;

    cvNamedWindow("Camera_Output", 1);    //Create window
    CvCapture* capture = cvCaptureFromCAM(CV_CAP_ANY);  //Capture using any camera connected to your system
    while(1){ //Create infinte loop for live streaming

        IplImage* frame = cvQueryFrame(capture); //Create image frames from capture

        //convert IplImage contour.jpg to Mat
        Mat matCon(frame);

        ImageData* data = new ImageData;

        data->image = matCon;

        data = detect.filter(data);

        cvShowImage("Camera_Output", frame);   //Show image frames on created window
        key = cvWaitKey(10);     //Capture Keyboard stroke
        if (char(key) == 27){
            break;      //If you hit ESC key loop will break.
        }
    }
    cvReleaseCapture(&capture); //Release capture.
    cvDestroyWindow("Camera_Output"); //Destroy Window
    return 0;
}

