#include "SequentialPipelineTest.h"
#include "PreProcessingFilterTest.h"

int main(int argc, char *argv[])
{
    SequentialPipelineTest sequentialPipelineTest;
    QTest::qExec(&sequentialPipelineTest, argc, argv);

    PreProcessingFilterTest preProcessingFilterTest;
    QTest::qExec(&preProcessingFilterTest, argc, argv);

    return 0;
}
