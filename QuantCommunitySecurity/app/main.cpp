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
    cout << "hello" << endl;
    Capturer* capturer = new RTSPCapturer("someUrl");
    Filter* faceDetect = new FaceDetectFilter("someLoc");
    CascadeClassifier eyeCascade1;
    eyeCascade1.load("haarcascade_eye.xml");
    CascadeClassifier eyeCascade2;
    eyeCascade2.load("haarcascade_eye_tree_eyeglasses.xml");
    Filter* preProc = new PreProcessingFilter(400, eyeCascade1, eyeCascade2);
    Persister* persister = new LocalPersister();
    Pipeline* pipeline = new SequentialPipeline();
    pipeline->attachCapturer(capturer);
    pipeline->attachFilter(faceDetect);
    pipeline->attachFilter(preProc);
    pipeline->attachPersister(persister);

    while (true)
    {
        pipeline->process(1);
        cout << "Processed Frame" << endl;
    }
    //QCoreApplication a(argc, argv);


    //return a.exec();
    return 0;
}
