#include "DatabasePersisterTest.h"
#include <QtDebug>
#include "DatabasePersistRequest.h"
#include "DatabasePersister.h"
#include "PostgreDatabasePersister.h"
#include <QDateTime>
using namespace std;
void DatabasePersisterTest::Test()
{

                string s = "Zane";
                QDateTime q = QDateTime::fromString("M1d1y9800:05:02",
                                                    "'M'M'd'd'y'yyhh:mm:ss");
                DatabasePersistRequest dpr = DatabasePersistRequest(s, q);

                DatabasePersister d = PostgreDatabasePersister();
                bool suc = d.persistImageFileData(dpr);
                QVERIFY(suc == true);








}
