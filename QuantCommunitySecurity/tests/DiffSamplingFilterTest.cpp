#include "DiffSamplingFilterTest.h"
#include "ImageData.h"
#include <QtDebug>
using namespace std;
void DiffSamplingFilterTest::filterTest()
{

                Mat src = imread("C:\\Users\\E102541\\Desktop\\Verushka\\nm1.png", CV_LOAD_IMAGE_COLOR);
                Mat src2 = imread("C:\\Users\\E102541\\Desktop\\Verushka\\nm2.png", CV_LOAD_IMAGE_COLOR);
                ImageData* testData = new ImageData();
                ImageData* testD = new ImageData();
                testData->addFace(src);
                Filter* diffSF = new DiffSamplingFilter(30.00);
                testD = diffSF->filter(testData);
                QVERIFY(testD == NULL);

                testData->image = src2;
                testData->addFace(src2);
                ImageData* testData2 = new ImageData();
                testData2 = diffSF->filter(testData);
                QVERIFY(testData2 == testData);




}
