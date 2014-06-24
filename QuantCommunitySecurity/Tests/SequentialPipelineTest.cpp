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
    Filter* expectedFilter = new FakeFilter();
    pipeline->attachFilter(expectedFilter);
    QCOMPARE(pipeline->getNumberOfFilters(), 1);
    Filter* actualFilter = pipeline->detachLastFilter();
    QCOMPARE(actualFilter,expectedFilter);
    QCOMPARE(pipeline->detachLastFilter(), NULL);
    QCOMPARE(pipeline->getNumberOfFilters(), 0);

    vector<Filter*> fakeFilters;
    for (int i = 0; i < 5; i++)
    {
        fakeFilters.push_back(new FakeFilter());
    }
    pipeline->attachFilters(fakeFilters);
    pipeline->attachFilter(expectedFilter);
    int expectedNumFilters = 6;
    QCOMPARE(pipeline->getNumberOfFilters(), expectedNumFilters);
    QCOMPARE(pipeline->detachLastFilter(), expectedFilter);
    QCOMPARE(pipeline->getNumberOfFilters(), --expectedNumFilters);
    for (int i = 4; i >= 0; i--)
    {
        QCOMPARE(pipeline->detachLastFilter(), fakeFilters[i]);
        QCOMPARE(pipeline->getNumberOfFilters(), --expectedNumFilters);
    }
}

void SequentialPipelineTest::processTest()
{
    FakeCapturer* fakeCapturer = new FakeCapturer(new ImageData());
    FakePersister* fakePersister = new FakePersister();
    vector<FakeFilter*> fakeFilters;
    for (int i = 0; i < 5; i++)
    {
        fakeFilters.push_back(new FakeFilter());
    }

    Pipeline* pipeline= new SequentialPipeline();
    pipeline->attachCapturer(fakeCapturer);
    pipeline->attachPersister(fakePersister);
    pipeline->attachFilters(fakeFilters);

    pipeline->process(1);

    QVERIFY(fakeCapturer->getCalledFlag());
    QVERIFY(fakePersister->getCalledFlag());
    for (int i = 0; i < 5; i++)
    {
        QVERIFY(fakeFilters[i]->getCalledFlag());
    }
}
