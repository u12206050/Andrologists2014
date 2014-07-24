#include "FacialFeatureRecognizerTest.h"
#include "DatabaseReaderTest.h"

int main(int argc, char *argv[])
{
    FacialFeatureRecognizerTest facialFeatureRecognizerTest;
	QTest::qExec(&facialFeatureRecognizerTest, argc, argv);

    DatabaseReaderTest databaseReaderTest;
	QTest::qExec(&databaseReaderTest, argc, argv);

    return 0;
}
