#include "FaceDetectFilterTest.h"

void FaceDetectFilterTest::filterTest()
{
    string classifier("../../testFiles/haarcascade_frontalface_alt.xml");
    string secondOpinion("../../testFiles/haarcascade_frontalface_alt_tree.xml");

    FaceDetectFilter* filter = new FaceDetectFilter(classifier, secondOpinion);

    ImageData* data = new ImageData();

    data->image = imread("../../testFiles/img19.jpg", CV_LOAD_IMAGE_UNCHANGED);
    data = filter->filter(data);
    unsigned int expectedNumFaces = 19;
	QVERIFY(data->faces.size() >= expectedNumFaces - 2 && data->faces.size() <= expectedNumFaces + 2);

    data->image = imread("../../testFiles/img2.jpg", CV_LOAD_IMAGE_UNCHANGED);
    data = filter->filter(data);
    expectedNumFaces = 2;
    QVERIFY(data->faces.size() == expectedNumFaces);

	data->image = imread("../../testFiles/same3.jpg", CV_LOAD_IMAGE_UNCHANGED);
    data = filter->filter(data);
    expectedNumFaces = 1;
    QVERIFY(data->faces.size() == expectedNumFaces);

    data->image = imread("../../testFiles/zeroFaces.jpg", CV_LOAD_IMAGE_UNCHANGED);
    data = filter->filter(data);
    expectedNumFaces = 0;
    QVERIFY(data->faces.size() == expectedNumFaces);
}


