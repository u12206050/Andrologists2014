#include "CaseAuthenticator.h"

CaseAuthenticator::CaseAuthenticator(QString& databaseType, QString& hostname, QString& databaseName, QString& username, QString& password, int port)
{
    database = QSqlDatabase::addDatabase(databaseType);
    database.setHostName(hostname);
    database.setDatabaseName(databaseName);
    database.setUserName(username);
    database.setPassword(password);
    database.setPort(port);
}

bool CaseAuthenticator::authenticate(int caseId, QString username, QString password)
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
