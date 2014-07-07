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
    QString videoLocation("/home/zane/mjpg_cap/video4.mjpg");
    Capturer* capturer = new RTSPCapturer(videoLocation);
    Filter* sampling = new DiffSamplingFilter(0.175);
    CascadeClassifier faceCascade;
    faceCascade.load("haarcascade_frontalface_alt_tree.xml");
    Filter* faceDetect = new FaceDetectFilter(faceCascade);
    CascadeClassifier eyeCascade1;
    eyeCascade1.load("haarcascade_eye.xml");
    CascadeClassifier eyeCascade2;
    eyeCascade2.load("haarcascade_eye_tree_eyeglasses.xml");
    Filter* preProc = new PreProcessingFilter(400, eyeCascade1, eyeCascade2);
    QString dir("../images/");
    Persister* persister = new LocalPersister(dir, 0);
    Pipeline* pipeline = new SequentialPipeline();
    pipeline->attachCapturer(capturer);
    pipeline->attachFilter(sampling);
    pipeline->attachFilter(faceDetect);
    //pipeline->attachFilter(preProc);
    pipeline->attachPersister(persister);

    //while (true)
   //{
        pipeline->process(650);
        cout << "Processed Frame" << endl;
  // }
    //QCoreApplication a(argc, argv);


    //return a.exec();
    return 0;
}
