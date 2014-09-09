#ifndef CASEAUTHENTICATOR_H
#define CASEAUTHENTICATOR_H

#include <string>
#include <QtSql>
#include "ErrorException.h"

using namespace std;

class CaseAuthenticator
{
    public:
        CaseAuthenticator(QString& databaseType, QString& hostname, QString& databaseName, QString& username, QString& password, int port);
        bool authenticate(int caseId, QString username, QString password);

    private:
        QSqlDatabase database;
};

#endif // CASEAUTHENTICATOR_H
