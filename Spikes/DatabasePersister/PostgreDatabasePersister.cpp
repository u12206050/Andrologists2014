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

PostgreDatabasePersister::PostgreDatabasePersister()
{

}

PostgreDatabasePersister::~PostgreDatabasePersister()
{

}

void PostgreDatabasePersister::persistImageFileData(DatabasePersistRequest request)
{
    string filename = request.originalImageFilename;
    QDateTime timestamp = request.timeStamp;

    insertIntoDatabase(filename, timestamp);

}

void PostgreDatabasePersister::viewDatabase()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("verush08");
    db.setPort(5432);

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

void PostgreDatabasePersister::insertIntoDatabase(string filename, QDateTime timestamp)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("dbPhotos");
    db.setUserName("postgres");
    db.setPassword("verush08");
    db.setPort(5432);

    if (db.open())
    {
       // cout << "******* Working *********" << endl;

        QSqlQuery query;
        QString file = QString::fromStdString(filename);

          query.prepare("INSERT INTO photos (photo_filename, photo_timestamp) "
          "VALUES (:filename, :time)");
          query.bindValue(":filename", file);
          query.bindValue(":time", timestamp);
          query.exec();

    }



}
