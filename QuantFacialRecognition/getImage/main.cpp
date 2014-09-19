#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "DatabaseReader.h"

#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

using namespace std;
using namespace cgicc;

#if _WIN32
#include <fcntl.h>
#include <io.h>

#define strcasecmp stricmp
#endif

void cgiError()
{
    // Most simple error handling
    cout << endl;
    exit(0);
}


void dumpFile(const char* filename)
{
    // Get the image type and send the headers

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
        } else {
            break;
        }
        }

        cout.flush();
    }
}


int main()
{
    #if _WIN32
    // Standard I/O is in text mode by default; since we intend
    // to send binary image data to standard output, we have to
    // set it to binary mode.
    // Error handling is tricky to say the least, so we have none.
    _fmode = _O_BINARY;
    if (_setmode(_fileno(stdin), _fmode) == -1) {}
    if (_setmode(_fileno(stdout), _fmode) == -1) {}
    #endif

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

    QString dbType("QPSQL");
    QString dbHost("localhost");
    QString dbName("quant");
    QString dbUser("postgres");
    QString dbPassword("root");

    DatabaseConnection* conn = new DatabaseConnection(dbType, dbHost, dbName, dbUser, dbPassword, 5432);

    DatabaseReader reader(conn);

    QString filename = reader.getImagePath(randomIdentifier, identifierType);

    dumpFile(filename.toStdString().c_str());

    return 0;
}
