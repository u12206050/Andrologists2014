#include "NSamplingFilterTest.h"
#include "ImageData.h"

void NSamplingFilterTest::filterTest()
{
    Mat src = imread("C:\\Users\\E102541\\Desktop\\Verushka\\nm1.png", CV_LOAD_IMAGE_COLOR);
    Mat src2 = imread("C:\\Users\\E102541\\Desktop\\Verushka\\nm2.png", CV_LOAD_IMAGE_COLOR);
    Mat src3 = imread("C:\\Users\\E102541\\Desktop\\Verushka\\nm3.png", CV_LOAD_IMAGE_COLOR);
    Mat src4 = imread("C:\\Users\\E102541\\Desktop\\Verushka\\nm4.png", CV_LOAD_IMAGE_COLOR);
    Mat src5 = imread("C:\\Users\\E102541\\Desktop\\Verushka\\nm5.png", CV_LOAD_IMAGE_COLOR);
    Mat src6 = imread("C:\\Users\\E102541\\Desktop\\Verushka\\nm6.png", CV_LOAD_IMAGE_COLOR);

    //n=1
    ImageData* testData = new ImageData();
    ImageData* testD = new ImageData();
    testData->image = src;
    testData->addFace(src);
    Filter* NSF = new NSamplingFilter(3);
    testD = NSF->filter(testData);
    QVERIFY(testD == NULL);

    //n=2
    testData->image = src2;
    testData->addFace(src2);
    //ImageData* testData2 = new ImageData();
    testD = NSF->filter(testData);
    QVERIFY(testD == NULL);

    //n=3 ------ yes
    testData->image = src3;
    testData->addFace(src3);
    //ImageData* testData2 = new ImageData();
    testD = NSF->filter(testData);
    QVERIFY(testD == testData);

    //n=4
    testData->image = src4;
    testData->addFace(src4);
    //ImageData* testData2 = new ImageData();
    testD = NSF->filter(testData);
    QVERIFY(testD == NULL);

    //n=5
    testData->image = src5;
    testData->addFace(src5);
    //ImageData* testData2 = new ImageData();
    testD = NSF->filter(testData);
    QVERIFY(testD == NULL);

    //n=6 ------ yes
    testData->image = src6;
    testData->addFace(src6);
    //ImageData* testData2 = new ImageData();
    testD = NSF->filter(testData);
    QVERIFY(testD == testData);
}
