#include <iostream>
#include "CaseManager.h"
#include "FacialFeatureRecognizer.h"
#include "PreProcessingFilter.h"
#include "FaceDetectFilter.h"

using namespace std;

int main()
{
    try
    {
        cout << "started" << endl;
        int caseId = 1;

        QString dbType("QPSQL");
        QString dbHost("127.0.0.1");
        QString dbName("quant");
        QString dbUser("postgres");
        QString dbPassword("root");

        DatabaseConnection* conn = new DatabaseConnection(dbType, dbHost, dbName, dbUser, dbPassword, 5432);

        string faceCascade = "/home/zane/Documents/COS301/MainProject/testFiles/haarcascade_frontalface_alt2.xml";
        Filter* faceDetect = new FaceDetectFilter(faceCascade);

        Filter* preProc = new PreProcessingFilter(140, 150,
                             "/home/zane/Documents/COS301/MainProject/testFiles/haarcascade_eye.xml",
                             "/home/zane/Documents/COS301/MainProject/testFiles/haarcascade_eye_tree_eyeglasses.xml");

        Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
        FacialFeatureRecognizer recognizer(model, 2300, conn, faceDetect, preProc);
        QString trainingFile("/home/zane/Documents/COS301/training1.xml");
        recognizer.loadTrainingFromXML(trainingFile);
        recognizer.processCase(caseId);
        cout << "end" << endl;
    }
    catch (ErrorException e)
    {
        cout << e.toString().toStdString() << endl;
    }

    return 0;
}
