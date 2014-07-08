#include "FaceDetectFilterTest.h"

void FaceDetectFilterTest::filterTest()
{
    CascadeClassifier classifier("haarcascade_frontalface_alt_tree.xml");

    FaceDetectFilter* filter = new FaceDetectFilter(classifier);

    ImageData* data = new ImageData();

    data->image = imread("img19.jpg", CV_LOAD_IMAGE_UNCHANGED);
    data = filter->filter(data);
    unsigned int expectedNumFaces = 19;
    QVERIFY(data->faces.size() == expectedNumFaces);

    data->image = imread("img2.jpg", CV_LOAD_IMAGE_UNCHANGED);
    data = filter->filter(data);
    expectedNumFaces = 2;
    QVERIFY(data->faces.size() == expectedNumFaces);

    data->image = imread("nm1.png", CV_LOAD_IMAGE_UNCHANGED);
    data = filter->filter(data);
    expectedNumFaces = 1;
    QVERIFY(data->faces.size() == expectedNumFaces);
}


