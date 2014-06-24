#include "SequentialPipelineTest.h"

int main(int argc, char *argv[])
{
    SequentialPipelineTest sequentialPipelineTest;
    QTest::qExec(&sequentialPipelineTest, argc, argv);

    return 0;
}
