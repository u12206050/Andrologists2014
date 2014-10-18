#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "DatabaseReader.h"
#include "ConnectionFileReader.h"

#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

using namespace std;
using namespace cgicc;

void cgiError()
{
    // Most simple error handling
    cout << endl;
    exit(0);
}


void dumpFile(const char* filename)
{
    cout << "Content-Type: " << "image/jpg" << endl;
    cout << endl;

    ifstream file(filename, ios::in | ios::binary);

    if (file)
    {
        while (!file.eof())
        {
            char buf[1024];

            file.read(buf, sizeof(buf));
            int count = file.gcount();
            if (count)
            {
                cout.write(buf, count);
            }
            else
            {
                break;
            }
        }

        cout.flush();
    }
}


int main()
{
    QString randomIdentifier;
    int identifierType;

    Cgicc cgi;

    form_iterator idenIter = cgi.getElement("image");
    if (idenIter != cgi.getElements().end())
    {
        randomIdentifier = QString((**idenIter).c_str());
    }

    form_iterator type = cgi.getElement("org");
    if (type != cgi.getElements().end())
    {
        identifierType = atoi((**type).c_str());
    }
    else
    {
        dumpFile(randomIdentifier.toStdString().c_str());
        return 0;
    }

    ConnectionFileReader connectionReader(QString("../Resources/connection.txt"));
    DatabaseConnection* conn = connectionReader.getDatabaseConnection();

    DatabaseReader reader(conn);

    try
    {
        QString filename = reader.getImagePath(randomIdentifier, identifierType);
        dumpFile(filename.toStdString().c_str());

    }
    catch (ErrorException e)
    {
        cout << e.toString().toStdString() << endl;
    }

    return 0;
}
