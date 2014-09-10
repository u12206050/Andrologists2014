#include "CaseManager.h"

#include <iostream>

using namespace std;

CaseManager::CaseManager(DatabaseConnection* databaseConnection, int caseId)
{
    this->databaseConnection = databaseConnection;
    this->caseId = caseId;
}


void CaseManager::updateCaseStatus(int faceId, double percentageMatch)
{
    string randomIdentifier = "";

    srand (time(NULL));
    for (int i = 0; i < 10; i++)
    {
        char c;
        int j = rand() % 4;
        if (j == 0)
        {
            c = (rand() % 10) + 48;
        }
        else if (j == 1)
        {
            c = (rand() % 26) + 65;
        }
        else
        {
            c = (rand() % 26) + 97;
        }
        randomIdentifier += c;
    }

    randomIdentifier += faceId;

    if (databaseConnection->getDatabase().open())
    {
        QSqlQuery query;
        query.prepare("INSERT INTO case_results "
                      "(face_id, case_id, percentage_match, random_identifier) "
                      "VALUES (:faceId, :caseId, :percentageMatch, :randomIdentifier)");
        query.bindValue(":faceId", faceId);
        query.bindValue(":caseId", caseId);
        query.bindValue(":percentageMatch", percentageMatch);
        QString qRandomIdentifier(randomIdentifier.c_str());
        query.bindValue(":randomIdentifier", qRandomIdentifier);
        if(!query.exec())
        {
            QString error("inserting case result.");
            throw ErrorException(error, 0);
        }
    }
    else
    {
        QString error("database closed.");
        throw ErrorException(error, 3);
    }
}

bool CaseManager::authenticateCase(QString username, QString password)
{
    if (caseId == 0)
    {
        return false;
    }
    if (databaseConnection->getDatabase().open())
    {
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM users, cases WHERE users.username = cases.username AND users.username = :userName AND cases.id = :caseId AND users.password = :password");
        query.bindValue(":userName", username);
        query.bindValue(":caseId", caseId);
        query.bindValue(":password", password);

        if(!query.exec())
        {
            cout << query.lastError().text().toStdString() << endl;
            QString error("Authenticating user");
            throw ErrorException(error, 0);
        }

        query.next();
        if (query.value(0).toInt() == 1)
        {
            return true;
        }
    }
    else
    {
        QString error("database closed.");
        throw ErrorException(error, 3);
    }

    return false;
}

int CaseManager::getCaseId()
{
    return caseId;
}
