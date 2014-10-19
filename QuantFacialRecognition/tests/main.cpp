#include "FacialFeatureRecognizerTest.h"
#include "DatabaseReaderTest.h"
#include "ConnectionFileReaderTest.h"

int main(int argc, char *argv[])
{
	FacialFeatureRecognizerTest facialFeatureRecognizerTest;
	QTest::qExec(&facialFeatureRecognizerTest, argc, argv);

	DatabaseReaderTest databaseReaderTest;
	QTest::qExec(&databaseReaderTest, argc, argv);

    ConnectionFileReaderTest connectionFileReaderTest;
    QTest::qExec(&connectionFileReaderTest, argc, argv);

    return 0;
}
