#include "NSamplingFilterTest.h"

void NSamplingFilterTest::filterTest()
{
    Filter* samplingFilter = new NSamplingFilter(3);
    ImageData* testData = new ImageData();

    ImageData* actual = samplingFilter->filter(testData);
    QVERIFY(actual == NULL);

    actual = samplingFilter->filter(testData);
    QVERIFY(actual == NULL);

    actual = samplingFilter->filter(testData);
    QVERIFY(actual == testData);

    actual = samplingFilter->filter(testData);
    QVERIFY(actual == NULL);

    actual = samplingFilter->filter(testData);
    QVERIFY(actual == NULL);

    actual = samplingFilter->filter(testData);
    QVERIFY(actual == testData);

    actual = samplingFilter->filter(testData);
    QVERIFY(actual == NULL);

    actual = samplingFilter->filter(testData);
    QVERIFY(actual == NULL);

    actual = samplingFilter->filter(testData);
    QVERIFY(actual == testData);
}
