#include <QCoreApplication>
#include "DatabasePersister.h"
#include "PostgreDatabasePersister.h"
#include <QDateTime>
#include <iostream>
#include "string.h"
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    PostgreDatabasePersister pst = PostgreDatabasePersister();
    string s = "Heelin";
    QDateTime q = QDateTime::fromString("M1d1y9800:01:02",
                                        "'M'M'd'd'y'yyhh:mm:ss");
    pst.insertIntoDatabase(s, q);
    cout << "Viewing..." << endl;
    pst.viewDatabase();

    return 0;
}
