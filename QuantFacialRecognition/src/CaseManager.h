#ifndef CASEMANAGER_H
#define CASEMANAGER_H

#include <QtSql>
#include <string>
#include "ErrorException.h"
#include "DatabaseConnection.h"
#include <sstream>

using namespace std;

class CaseManager
{
    public:
        CaseManager(DatabaseConnection* databaseConnection, int caseId);
        void updateCaseStatus(int faceId, double percentageMatch);
        bool authenticateCase(QString username, QString password);
        int getCaseId();
        void setProgress(int progress);
        void setStatus(string status);

    private:
        DatabaseConnection* databaseConnection;
        int caseId;
};

#endif // CASEMANAGER_H
