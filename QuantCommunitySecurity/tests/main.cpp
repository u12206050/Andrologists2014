#include "SequentialPipelineTest.h"
#include "PreProcessingFilterTest.h"
#include "DiffSamplingFilterTest.h"
#include "NSamplingFilterTest.h"
#include "FaceDetectFilterTest.h"
#include "LocalPersisterTest.h"
#include "DatabasePersisterTest.h"
#include "StreamCapturerTest.h"

int main(int argc, char *argv[])
{
    SequentialPipelineTest sequentialPipelineTest;
    QTest::qExec(&sequentialPipelineTest, argc, argv);

    PreProcessingFilterTest preProcessingFilterTest;
    QTest::qExec(&preProcessingFilterTest, argc, argv);

    DiffSamplingFilterTest diffSamplingFilterTest;
    QTest::qExec(&diffSamplingFilterTest, argc, argv);

    NSamplingFilterTest nSamplingFilterTest;
    QTest::qExec(&nSamplingFilterTest, argc, argv);

    FaceDetectFilterTest faceDetectFilterTest;
    QTest::qExec(&faceDetectFilterTest, argc, argv);

    LocalPersisterTest localPersisterTest;
    QTest::qExec(&localPersisterTest, argc, argv);

    DatabasePersisterTest databasePersisterTest;
    QTest::qExec(&databasePersisterTest, argc, argv);

	StreamCapturerTest streamCapturerTest;
	QTest::qExec(&streamCapturerTest, argc, argv);

    return 0;
}
