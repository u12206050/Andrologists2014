#include "PostgreDatabasePersister.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSql>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QSqlError>
#include <qsqlresult.h>
#include <qstring.h>
#include <stdio.h>
#include "string.h"
#include <iostream>
#include <QDebug>
#include <QtSql/QSqlDriverPlugin>
#include <QVariant>
using namespace std;

PostgreDatabasePersister::PostgreDatabasePersister(QString& databaseType, QString& hostname, QString& databaseName, QString& username, QString& password, int port)
{
    database = QSqlDatabase::addDatabase(databaseType);
    database.setHostName(hostname);
    database.setDatabaseName(databaseName);
    database.setUserName(username);
    database.setPassword(password);
    database.setPort(port);
}

PostgreDatabasePersister::~PostgreDatabasePersister()
{

}

bool PostgreDatabasePersister::persistImageFileData(DatabasePersistRequest request)
{
    return insertIntoDatabase(request.originalImageFilename, request.timeStamp);
}

void PostgreDatabasePersister::viewDatabase()
{

    QSqlQuery query;

      if(db.open()){
          QString dbOutput = "select * from pg_database;";
          query.exec(dbOutput);
          while(query.next()){
              QVariant qv = query.value(0);
              QString qs = qv.toString();

              cout << qs.toStdString() << endl;
               }
              db.setDatabaseName("dbPhotos");
              cout << "here too" << endl;
              if(db.open()){
                     if (db.tables().contains( QLatin1String("photos")))
                       {
                             cout << "photos table exists" << endl;
                        }
                     else
                         cout << "no such thing" << endl;



                QString dbOutput2 = "SELECT * FROM photos;";
              query.exec(dbOutput2);
              while(query.next()){
                  QVariant qv = query.value(0);
                  QString qs = qv.toString();
                  QVariant qv2 = query.value(1);
                  QString qs2 = qv2.toString();
                  QVariant qv3 = query.value(2);
                  QString qs3 = qv3.toString();
                  cout << "photo id: " << qs.toStdString();
                  cout << " photo filename: " << qs2.toStdString();
                  cout << " photo timestamp: " << qs3.toStdString() << endl;
                }
              if (!query.exec())
               qDebug() << "SQL ERROR: " << query.lastError().text();

              }
              else
              {
                  cout << "didn't open " << endl;
              }


          db.close();
      }else{
          cout << "problem" << endl;
      }


}

bool PostgreDatabasePersister::insertIntoDatabase(QString& filename, QDateTime timestamp)
{
    if (database.open())
    {
       // cout << "******* Working *********" << endl;

        QSqlQuery query;

          query.prepare("INSERT INTO photos (photo_filename, photo_timestamp) "
          "VALUES (:filename, :time)");
          query.bindValue(":filename", filename);
          query.bindValue(":time", timestamp);
          if(query.exec())
              return true;

    }

        return false;



}

