#ifndef SEQUENTIALPIPELINETEST_H
#define SEQUENTIALPIPELINETEST_H

#include <QtTest/QtTest>
#include "Pipeline.h"
#include "Fakes/FakeCapturer.h"
#include "Fakes/FakeFilter.h"
#include "Fakes/FakePersister.h"

class SequentialPipelineTest : public QObject
{
    Q_OBJECT
private slots:
    void attachAndDetachCapturerTest();
    void attachAndDetachPersisterTest();
    void attachAndDetachFilterTests();
    void processTest();
};

QTEST_MAIN(SequentialPipelineTest)

#endif // PIPELINETEST_H
