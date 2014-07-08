#include "SequentialPipelineTest.h"
#include "PreProcessingFilterTest.h"
#include "DiffSamplingFilterTest.h"
#include "NSamplingFilterTest.h"
#include "FaceDetectFilterTest.h"

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

    return 0;
}
