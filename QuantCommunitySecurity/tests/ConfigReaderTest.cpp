#include "ConfigReaderTest.h"

void ConfigReaderTest::configReaderTest()
{
	try
	{
		ConfigReader reader("../../testFiles/configTest.txt");
	}
	catch (ErrorException e)
	{
		switch (e.getErrorCode())
		{
			case 0:
				QVERIFY(false);
				break;
			case 1:
				QVERIFY(false);
				break;
			case 2:
				QVERIFY(false);
				break;
			case 3:
				QVERIFY(false);
				break;
			case 4:
				QVERIFY(false);
				break;
			case 5:
				QVERIFY(false);
				break;
			default:
				QVERIFY(false);
		}
	}
}
