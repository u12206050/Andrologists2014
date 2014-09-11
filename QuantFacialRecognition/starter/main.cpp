#include <iostream>
#include <cstdlib>
#include <string>
#include "CaseManager.h"
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[])
{
    /*if (argc != 3)
    {
        cout << "2" << endl;
        return 1;
    }

    int caseId = atoi(argv[0]);
    QString username = argv[1];
    QString password = argv[2];*/

    int caseId = 1;
    QString username = "zane";
    QString password = "zane";

    QString dbType("QPSQL");
    QString dbHost("localhost");
    QString dbName("quant");
    QString dbUser("postgres");
    QString dbPassword("root");

    DatabaseConnection* conn = new DatabaseConnection(dbType, dbHost, dbName, dbUser, dbPassword, 5432);

    CaseManager manager(conn, caseId);
    if (!manager.authenticateCase(username, password))
    {
        cout << "1" << endl;\
        return 1;
    }
    cout << "0" << endl;

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

    switch (pid) {
    case -1: /* Error */
        std::cerr << "Uh-Oh! fork() failed.\n";
        exit(1);
    case 0: /* Child process */
        execl(programPath, NULL); /* Execute the program */
        std::cerr << "Uh-Oh! execl() failed!"; /* execl doesn't return unless there's an error */
        exit(1);
    default: /* Parent process */
        std::cout << "Process created with pid " << pid << "\n";
        int status;

        /*while (!WIFEXITED(status))
        {
            waitpid(pid, status, 0);
        }

        std::cout << "Process exited with " << WEXITSTATUS(status) << "\n";*/

        return 0;
    }
    //}
}
