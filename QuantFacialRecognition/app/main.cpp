#include <iostream>
#include "CaseManager.h"
#include "FacialFeatureRecognizer.h"
#include "PreProcessingFilter.h"
#include "FaceDetectFilter.h"
#include <fstream>
#include <unistd.h>
#include "ConnectionFileReader.h"

using namespace std;

int main(int argc, char* argv[])
{
    daemon(0, 0);

    try
    {
        //cout << "started: " << argv[0] << endl;
        int caseId = atoi(argv[0]);

        fstream file;
        file.open("/home/zane/Documents/COS301/MainProject/log.txt", ios::out);
        file << "Started facerec process, caseId: " << caseId << endl;

        //cout << "caseId: " << caseId << endl;

        ConnectionFileReader reader(QString("../../Resources/connectio.txt"));
        DatabaseConnection* conn = reader.getDatabaseConnection();

        string faceCascade = "/home/zane/Documents/COS301/MainProject/testFiles/haarcascade_frontalface_alt2.xml";
        Filter* faceDetect = new FaceDetectFilter(faceCascade);

        Filter* preProc = new PreProcessingFilter(140, 150,
                             "/home/zane/Documents/COS301/MainProject/testFiles/haarcascade_eye.xml",
                             "/home/zane/Documents/COS301/MainProject/testFiles/haarcascade_eye_tree_eyeglasses.xml");

        Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
        FacialFeatureRecognizer recognizer(model, 1900, conn, faceDetect, preProc);
        QString trainingFile("/home/zane/Documents/COS301/training1.xml");
        recognizer.loadTrainingFromXML(trainingFile);
        file << "busy facerec, caseId: " << caseId << endl;
        recognizer.processCase(caseId);
        file << "end facerec, caseId: " << caseId << endl << endl;
        file.close();
        //cout << "end" << endl;
    }
    catch (ErrorException e)
    {
        cout << e.toString().toStdString() << endl;
    }

    return 0;
}
