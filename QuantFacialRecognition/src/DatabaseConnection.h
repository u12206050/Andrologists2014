#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QtSql>

class DatabaseConnection
{
    public:
        DatabaseConnection(QString& databaseType, QString& hostname, QString& databaseName, QString& username, QString& password, int port);
        QSqlDatabase getDatabase();

    private:
        QSqlDatabase database;

};

#endif // DATABASECONNECTION_H
