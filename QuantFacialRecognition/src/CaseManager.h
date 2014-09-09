#ifndef CASEMANAGER_H
#define CASEMANAGER_H

#include <QtSql>
#include <string>
#include "ErrorException.h"

using namespace std;

class CaseManager
{
    public:
        CaseManager(QSqlDatabase database, int caseId);
        void updateCaseStatus(int faceId, double percentageMatch);
        bool authenticateCase(QString username, QString password);
        int getCaseId();

    private:
        QSqlDatabase database;
        int caseId;
};

#endif // CASEMANAGER_H
