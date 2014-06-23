#include "SequentialPipelineTest.h"

void SequentialPipelineTest::attachAndDetachCapturerTest()
{
    Capturer* expected = new FakeCapturer(NULL);
    Pipeline* pipeline = new SequentialPipeline();
    pipeline->attachCapturer(expected);
    Capturer* actual = pipeline->detachCapturer();
    QCOMPARE(actual, expected);
    actual = pipeline->detachCapturer();
    QCOMPARE(actual, NULL);
    pipeline->attachCapturer(expected);
    actual = pipeline->detachCapturer();
    QCOMPARE(actual,expected);
}

void SequentialPipelineTest::attachAndDetachPersisterTest()
{
    Persister* expected = new FakePersister(NULL);
    Pipeline* pipeline = new SequentialPipeline();
    pipeline->attachPersister(expected);
    Persister* actual = pipeline->detachPersister();
    QCOMPARE(actual, expected);
    actual = pipeline->detachPersister();
    QCOMPARE(actual, NULL);
    pipeline->attachPersister(expected);
    actual = pipeline->detachPersister();
    QCOMPARE(actual,expected);
}

void SequentialPipelineTest::attachAndDetachFiltersTest()
{
    Pipeline* pipeline = new SequentialPipeline();
}

void SequentialPipelineTest::processTest()
{

}
