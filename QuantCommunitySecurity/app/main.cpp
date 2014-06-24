#include <QCoreApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "hello" << endl;
    QCoreApplication a(argc, argv);

    return a.exec();
}
