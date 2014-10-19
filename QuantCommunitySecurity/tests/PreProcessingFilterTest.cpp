#include "PreProcessingFilterTest.h"

void PreProcessingFilterTest::targetSizeTest()
{
    Mat face = imread("../../testFiles/testFace.jpg", CV_LOAD_IMAGE_COLOR);
    ImageData* testData = new ImageData(face, 0);
    testData->addFace(face);
	int targetWidth = 400;
    int targetHeight = 400;
	Filter* preProcFilter = new PreProcessingFilter(targetWidth, targetHeight);
    testData = preProcFilter->filter(testData);
    Mat preProcFace = testData->faces[0];
    QCOMPARE(preProcFace.cols, targetWidth);
    QCOMPARE(preProcFace.rows, targetHeight);
}

void PreProcessingFilterTest::greyScaleTest()
{
    Mat face = imread("../../testFiles/testFace.jpg", CV_LOAD_IMAGE_COLOR);
    ImageData* testData = new ImageData(face, 0);
    testData->addFace(face);
    int targetWidth = 400;
    int targetHeight = 400;
	Filter* preProcFilter = new PreProcessingFilter(targetWidth, targetHeight);
    testData = preProcFilter->filter(testData);
    Mat preProcFace = testData->faces[0];
    QCOMPARE(preProcFace.channels(), 1);
}
