#include "SequentialPipelineTest.h"
#include "PreProcessingFilterTest.h"
#include "DiffSamplingFilterTest.h"

int main(int argc, char *argv[])
{
    //SequentialPipelineTest sequentialPipelineTest;
    //QTest::qExec(&sequentialPipelineTest, argc, argv);

    //PreProcessingFilterTest preProcessingFilterTest;
    //QTest::qExec(&preProcessingFilterTest, argc, argv);

    DiffSamplingFilterTest diffSamplingFilterTest;
    QTest::qExec(&diffSamplingFilterTest, argc, argv);

    return 0;
}
