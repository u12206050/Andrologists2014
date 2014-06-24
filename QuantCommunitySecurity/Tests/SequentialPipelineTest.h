#ifndef SEQUENTIALPIPELINETEST_H
#define SEQUENTIALPIPELINETEST_H

#include <QtTest/QtTest>
#include "SequentialPipeline.h"
#include "Fakes/FakeCapturer.h"
#include "Fakes/FakeFilter.h"
#include "Fakes/FakePersister.h"

using namespace std;

class SequentialPipelineTest : public QObject
{
    Q_OBJECT
private slots:
    void attachAndDetachCapturerTest();
    void attachAndDetachPersisterTest();
    void attachAndDetachFilterTest();
    void processTest();
};

#endif // PIPELINETEST_H
