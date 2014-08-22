/*#include <QCoreApplication>*/
#include <iostream>

#include "StreamCapturer.h"
#include "LocalPersister.h"
#include "DiffSamplingFilter.h"
#include "NSamplingFilter.h"
#include "SequentialPipeline.h"
#include "FaceDetectFilter.h"
#include "ShowImageFilter.h"
#include "PreProcessingFilter.h"
#include "ConfigReader.h"

using namespace std;
using namespace cv;

int main(/*int argc, char *argv[]*/)
{
	try
	{
		ConfigReader reader("../../testFiles/configTest.txt");
	}
	catch (ErrorException e)
	{
		cout << e.toString().toStdString() << endl;
	}

	return 1;

	QString videoLocation("/home/zane/mjpg_cap/video4.mjpg");
    Capturer* capturer = new StreamCapturer(0);

    QString windowName("Video Stream");
    Filter* imageShower = new ShowImageFilter(windowName);

    Filter* sampling = new DiffSamplingFilter(0.16);

    string faceCascade = "/home/zane/Documents/COS301/MainProject/testFiles/haarcascade_frontalface_alt.xml";
    string secondOpinion = "/home/zane/Documents/COS301/MainProject/testFiles/haarcascade_frontalface_alt_tree.xml";
    Filter* faceDetect = new FaceDetectFilter(faceCascade, secondOpinion);

//    CascadeClassifier eyeCascade1;
//    eyeCascade1.load("haarcascade_eye.xml");
//    CascadeClassifier eyeCascade2;
//    eyeCascade2.load("haarcascade_eye_tree_eyeglasses.xml");
//    Filter* preProc = new PreProcessingFilter(400, eyeCascade1, eyeCascade2);

	QString dir("../images/");
    Persister* persister = new LocalPersister(dir, 0);

    Pipeline* pipeline = new SequentialPipeline();
    pipeline->attachCapturer(capturer);
    pipeline->attachFilter(imageShower);
    //pipeline->attachFilter(sampling);
    pipeline->attachFilter(faceDetect);
    //pipeline->attachFilter(preProc);
    pipeline->attachPersister(persister);

    for (int i = 0; i < 650; i++)
    {
        pipeline->process(1);
        cout << "Processed Frame" << endl;
    }

    //QCoreApplication a(argc, argv);


	//return a.exec();
    return 0;
}
