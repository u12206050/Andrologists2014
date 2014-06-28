#include "FaceDetectFilterTest.h"
#include "ImageData.h"

void FaceDetectFilterTest::filterTest()
{
    FaceDetectFilter* actual = new FaceDetectFilter("haarcascade_frontalface_alt_tree.xml");

    Mat image;
    image = imread("img2.jpg", CV_LOAD_IMAGE_COLOR);
    ImageData* data = new ImageData();
    data->image = image;
    data = actual->filter(data);

    QVERIFY(data->faces.size() == 2);
    //QCOMPARE(data->faces.size(), 1);
    //QVERIFY(actual == NULL);
}


