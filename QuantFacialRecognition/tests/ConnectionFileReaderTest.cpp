#include "ConnectionFileReaderTest.h"

void ConnectionFileReaderTest::parseTest()
{
    ConnectionFileReader reader(QString("../../testFiles/connectionTest.txt"));
    DatabaseConnection* connection = reader.getDatabaseConnection();
    QString type = connection->getDatabase().driverName();
    QString host = connection->getDatabase().hostName();
    QString name = connection->getDatabase().databaseName();
    QString username = connection->getDatabase().userName();
    QString password = connection->getDatabase().password();
    int port = connection->getDatabase().port();

    QCOMPARE(type, QString("QPSQL"));
    QCOMPARE(host, QString("localhost"));
    QCOMPARE(name, QString("quant"));
    QCOMPARE(username, QString("postgre"));
    QCOMPARE(password, QString("root"));
    QCOMPARE(port, 5432);
}

