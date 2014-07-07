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
using namespace std;

PostgreDatabasePersister::PostgreDatabasePersister()
{

}

PostgreDatabasePersister::~PostgreDatabasePersister()
{

}

void PostgreDatabasePersister::persistImageFileData(DatabasePersistRequest request)
{

}

void PostgreDatabasePersister::connectToDatabase()
{

}

void PostgreDatabasePersister::insertIntoDatabase(string filename, QDateTime timestamp)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("dbPhotos");
    db.setUserName("postgres");
    db.setPassword("verush08");
    db.setPort(5432);
   // bool ok = db.open();

    if (db.open())
    {
        cout << "******* Working *********" << endl;



        QSqlQuery userQuery(db);



        // userQuery.exec("INSERT INTO tbPhotos(photo_id, photo_filename, photo_timestamp)"
               //                "VALUES (?, ?, ?)");

        cout << "Here............" <<endl;


    // if (!userQuery.prepare("SELECT * FROM 'tbPhotos' WHERE photo_id = 1"))
  //   std::cout << "prepare failed" << std::endl;


     /*   PREPARE prepStat (QString) AS
            SELECT * FROM tbPhotos;
        EXECUTE prepStat();*/


        userQuery.prepare(QString('SELECT * FROM "tbPhotos" '));
      //  if (!userQuery.prepare())
        // qDebug() << "SQL ERROR: " << userQuery.lastError().text();
        userQuery.exec();


   //     userQuery.exec(QString('SELECT * FROM "tbPhotos" '));
    cout << "Here again............" <<endl;



       // userQuery.bindValue(":username", username);

       /* userQuery.first();


        if (userQuery.exec()) {
           while (userQuery.next()) {
            int photoID = userQuery.value(0).toInt();
            QString fname = userQuery.value(1).toString();
            QDateTime ts = userQuery.value(2).toDateTime();



            cout<< "id: " << photoID  << endl; //<< " name: " << fname << " timestamp: " << ts << endl;
           }
        }
            else*/
           if (!userQuery.exec())
            qDebug() << "SQL ERROR: " << userQuery.lastError().text();




        //test select
       /* QSqlQuery query = db.exec("SELECT * FROM tbPhotos");
          while (query.next()) {
                 QString pfilename = query.value(0).toString();
                 qDebug() << pfilename << endl;
                // cout << "filename: " << pfilename << endl;
             }*/
          /*while (query.next()) {
                 QString name = query.value(0).toString();
                 int salary = query.value(1).toInt();
                 qDebug() << name << salary;
             }*/



    /*    QSqlQuery qsql = db.exec("INSERT INTO tbPhotos(photo_id, photo_filename, photo_timestamp)"
                       "VALUES (?, ?, ?)");

        QString file = QString::fromStdString(filename);

          qsql.bindValue(0, 1);
          qsql.bindValue(1, file);
          qsql.bindValue(2, timestamp);
        //  qsql.exec();

          if (qsql.exec())
          {
              cout << "all is good" <<endl;
          }*/


    }



}
