#include "PreProcessingFilterTest.h"

void PreProcessingFilterTest::targetSizeTest()
{
    Mat face = imread("../../testFiles/testFace.jpg", CV_LOAD_IMAGE_COLOR);
    ImageData* testData = new ImageData(face, 0);
    testData->addFace(face);
    CascadeClassifier eyeCascade1;
    eyeCascade1.load("../../testFiles/haarcascade_eye.xml");
    CascadeClassifier eyeCascade2;
    eyeCascade2.load("../../testFiles/haarcascade_eye_tree_eyeglasses.xml");
    int targetSize = 400;
    Filter* preProcFilter = new PreProcessingFilter(targetSize, eyeCascade1, eyeCascade2);
    testData = preProcFilter->filter(testData);
    Mat preProcFace = testData->faces[0];
    QCOMPARE(preProcFace.cols, targetSize);
    QCOMPARE(preProcFace.rows, targetSize);
}

void PreProcessingFilterTest::greyScaleTest()
{
    Mat face = imread("../../testFiles/testFace.jpg", CV_LOAD_IMAGE_COLOR);
    ImageData* testData = new ImageData(face, 0);
    testData->addFace(face);
    CascadeClassifier eyeCascade1;
    eyeCascade1.load("../../testFiles/haarcascade_eye.xml");
    CascadeClassifier eyeCascade2;
    eyeCascade2.load("../../testFiles/haarcascade_eye_tree_eyeglasses.xml");
    int targetSize = 400;
    Filter* preProcFilter = new PreProcessingFilter(targetSize, eyeCascade1, eyeCascade2);
    testData = preProcFilter->filter(testData);
    Mat preProcFace = testData->faces[0];
    QCOMPARE(preProcFace.channels(), 1);
}
