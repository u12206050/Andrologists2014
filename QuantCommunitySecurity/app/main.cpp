#include <QCoreApplication>
#include <iostream>

#include "RTSPCapturer.h"
#include "LocalPersister.h"
#include "DiffSamplingFilter.h"
#include "NSamplingFilter.h"
#include "SequentialPipeline.h"
#include "FaceDetectFilter.h"
#include "PreProcessingFilter.h"

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{

    //rtsp://192.168.129.251/live.sdp
    //http://192.168.134.252/video4.mjpg
    //http://192.168.129.251/?action=stream?dummy=param.mjpg
    Capturer* capturer = new RTSPCapturer("/home/zane/mjpg_cap/video4.mjpg/");
  /*  Filter* faceDetect = new FaceDetectFilter("haarcascade_frontalface_alt_tree.xml");
    CascadeClassifier eyeCascade1;
    eyeCascade1.load("haarcascade_eye.xml");
    CascadeClassifier eyeCascade2;
    eyeCascade2.load("haarcascade_eye_tree_eyeglasses.xml");
    Filter* preProc = new PreProcessingFilter(400, eyeCascade1, eyeCascade2);
    Persister* persister = new LocalPersister("/home/zane/Documents/COS301/MainProject/test/");
    Pipeline* pipeline = new SequentialPipeline();
    pipeline->attachCapturer(capturer);
    pipeline->attachFilter(faceDetect);
    pipeline->attachFilter(preProc);
    pipeline->attachPersister(persister);

    while (true)
    {
        pipeline->process(1);
        cout << "Processed Frame" << endl;
   }*/
    //QCoreApplication a(argc, argv);


    //return a.exec();
    return 0;
}
