#include "CaseManager.h"

CaseManager::CaseManager(QSqlDatabase database, int caseId)
{
    this->database = database;
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

    if (database.open())
    {
        QSqlQuery query;
        query.prepare("INSERT INTO case_results "
                      "(face_id, case_id, percentage_match, random_identifier) "
                      "VALUES (:faceId, :caseId, :percentageMatch, :randomIdentifier)");
        query.bindValue(":faceId", faceId);
        query.bindValue(":caseId", caseId);
        query.bindValue(":pecentageMatch", percentageMatch);
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

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users, cases WHERE users.userName = cases.userName AND users.userName = :userName AND cases.case.id = :caseId AND users.password = :password");
    query.bindValue(":userName", username);
    query.bindValue(":caseId", caseId);
    query.bindValue(":password", password);


    if(!query.exec())
    {
        QString error("Authenticating user");
        throw ErrorException(error, 0);
    }

    if (query.value(0).toInt() == 1)
    {
        return true;
    }

    return false;
}

int CaseManager::getCaseId()
{
    return caseId;
}
