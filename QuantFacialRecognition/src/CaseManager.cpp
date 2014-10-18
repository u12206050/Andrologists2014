#include "CaseManager.h"

#include <iostream>
#include <sstream>

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

    stringstream ss;
    ss << faceId;
    string strFaceId;
    ss >> strFaceId;
    randomIdentifier += strFaceId;

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

        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE cases "
                      "SET num_results = num_results +1 "
                      "WHERE id = :caseId");
        updateQuery.bindValue(":caseId", caseId);
        if(!updateQuery.exec())
        {
            QString error("updating case result.");
            throw ErrorException(error, 1);
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
        query.prepare("SELECT COUNT(*) FROM users, cases WHERE users.username = cases.username AND users.username = :userName AND cases.id = :caseId AND users.password = crypt(:password, '2a068uKrXaZiFsbdet62kkZSSOida')");
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

void CaseManager::setProgress(int progress)
{
    if (databaseConnection->getDatabase().open())
    {
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE cases SET progress = :progress WHERE id = :caseId");
        updateQuery.bindValue(":caseId", caseId);
        updateQuery.bindValue(":progress", progress);
        if(!updateQuery.exec())
        {
            QString error("updating case progress.");
            throw ErrorException(error, 0);
        }
    }
    else
    {
        QString error("database closed.");
        throw ErrorException(error, 3);
    }
}

void CaseManager::setStatus(string status)
{
    if (databaseConnection->getDatabase().open())
    {
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE cases SET status = :status WHERE id = :caseId");
        updateQuery.bindValue(":caseId", caseId);
        updateQuery.bindValue(":status", QString(status.c_str()));
        if(!updateQuery.exec())
        {
            QString error("updating case progress.");
            throw ErrorException(error, 0);
        }
    }
    else
    {
        QString error("database closed.");
        throw ErrorException(error, 3);
    }
}
