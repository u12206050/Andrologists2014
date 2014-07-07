#include "DiffSamplingFilterTest.h"

void DiffSamplingFilterTest::filterTest()
{
    Filter* samplingFilter = new DiffSamplingFilter(0.1);

    Mat src = imread("same1.jpg", CV_LOAD_IMAGE_UNCHANGED);
    ImageData* imageData = new ImageData();
    imageData->image = src;
    imageData = samplingFilter->filter(imageData);
    QVERIFY(imageData != NULL);

    Mat src2 = imread("same11.jpg", CV_LOAD_IMAGE_UNCHANGED);
    imageData = new ImageData();
    imageData->image = src2;
    imageData = samplingFilter->filter(imageData);
    QVERIFY(imageData == NULL);

    Mat src3 = imread("same2.jpg", CV_LOAD_IMAGE_UNCHANGED);
    imageData = new ImageData();
    imageData->image = src3;
    imageData = samplingFilter->filter(imageData);
    QVERIFY(imageData != NULL);

    Mat src4 = imread("same3.jpg", CV_LOAD_IMAGE_UNCHANGED);
    imageData = new ImageData();
    imageData->image = src4;
    imageData = samplingFilter->filter(imageData);
    QVERIFY(imageData != NULL);
}
