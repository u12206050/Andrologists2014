#include <iostream>
#include <cstdlib>
#include <string>
#include "CaseManager.h"
#include <unistd.h>
#include <sstream>

#include "ConnectionFileReader.h"

#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

using namespace std;
using namespace cgicc;

int main()
{
    Cgicc cgi;

    int caseId;
    QString username;
    QString password;

    form_iterator userIter = cgi.getElement("user");
    if (userIter != cgi.getElements().end())
    {
       username = QString((**userIter).c_str());
    }

    form_iterator passIter = cgi.getElement("pass");
    if (passIter != cgi.getElements().end())
    {
       password = QString((**passIter).c_str());
    }

    form_iterator caseIter = cgi.getElement("caseID");
    if (caseIter != cgi.getElements().end())
    {
       caseId = atoi((**caseIter).c_str());
    }

    cout << HTTPHTMLHeader();

    ConnectionFileReader connectionReader(QString("../Resources/connection.txt"));
    DatabaseConnection* conn = connectionReader.getDatabaseConnection();


    CaseManager manager(conn, caseId);
    if (!manager.authenticateCase(username, password))
    {
        cout << "Could not authenticate user" << endl;
        return 1;
    }

	char* programPath = "/home/zane/Documents/COS301/MainProject/build-QuantFacialRecognition-Desktop_Qt_5_3_0_GCC_64bit-Debug/app/app";

    pid_t pid = fork();
    stringstream ss;
    ss << caseId;
    string strCaseId;
    ss >> strCaseId;

    switch (pid)
    {
        case -1:
            cout << "Could not start new process" << "\n";
            exit(1);
        case 0:
            execl(programPath, strCaseId.c_str(), NULL);
            std::cerr << "Uh-Oh! execl() failed!";
            cout << "Could not start new process" << "\n";
            exit(1);
        default:
            std::cout << "1";

        return 0;
    }
}
