#ifndef SEQUENTIALPIPELINETEST_H
#define SEQUENTIALPIPELINETEST_H

#include <QtTest/QtTest>
#include "SequentialPipeline.h"
#include "FakeCapturer.h"
#include "FakeFilter.h"
#include "FakePersister.h"

class SequentialPipelineTest : public QObject
{
    Q_OBJECT
    private slots:
        void attachAndDetachCapturerTest();
        void attachAndDetachPersisterTest();
        void attachAndDetachFilterTest();
        void processTest();
};

#endif // SEQUENTIALPIPELINETEST_H
