#include <iostream>
#include <cstdlib>
#include <string>
#include "CaseManager.h"
#include <unistd.h>
#include <sstream>

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

    // Send HTTP header
    cout << HTTPHTMLHeader() << endl;
    /*
    // Set up the HTML document
    cout << html() << head(title("cgicc example")) << endl;
    cout << body() << endl;

    cout << username.toStdString() << endl;
    cout << password.toStdString() << endl;
    cout << caseId << endl;

    cout << body() << html();*/

    QString dbType("QPSQL");
    QString dbHost("localhost");
    QString dbName("quant");
    QString dbUser("postgres");
    QString dbPassword("root");

    DatabaseConnection* conn = new DatabaseConnection(dbType, dbHost, dbName, dbUser, dbPassword, 5432);

    CaseManager manager(conn, caseId);
    if (!manager.authenticateCase(username, password))
    {
        cout << "Could not authenticate user" << endl;\
        return 1;
    }

    /*if (WINDOWS)
    {
        LPCTSTR lpApplicationName = "C:/Windows/System32/cmd.exe"; // The program to be executed

        LPSTARTUPINFO lpStartupInfo;
        LPPROCESS_INFORMATION lpProcessInfo;

        memset(&lpStartupInfo, 0, sizeof(lpStartupInfo));
        memset(&lpProcessInfo, 0, sizeof(lpProcessInfo));

        // Create the process
        if (!CreateProcess(lpApplicationName,
                           NULL, NULL, NULL,
                           NULL, NULL, NULL, NULL,
                           lpStartupInfo,
                           lpProcessInformation
                          )
           ) {
            std::cerr << "Uh-Oh! CreateProcess() failed to start program \"" << lpApplicationName << "\"\n";
            exit(1);
        }

        std::cout << "Started program \"" << lpApplicationName << "\" successfully\n";

    }
    if (LINUX)
    {*/
    char* programPath = "/home/zane/Documents/COS301/MainProject/build-QuantFacialRecognition-Desktop_Qt_5_3_GCC_32bit-Debug/app/app";

    pid_t pid = fork(); /* Create a child process */
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
            execl(programPath, strCaseId.c_str(), NULL); /* Execute the program */
            std::cerr << "Uh-Oh! execl() failed!"; /* execl doesn't return unless there's an error */
            cout << "Could not start new process" << "\n";
            exit(1);
        default: /* Parent process */
            std::cout << "1" << "\n";

        return 0;
    }
}
