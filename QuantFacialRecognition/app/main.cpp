#include <iostream>
#include "CaseManager.h"
#include "FacialFeatureRecognizer.h"
#include "PreProcessingFilter.h"
#include "FaceDetectFilter.h"
#include <unistd.h>
#include "ConnectionFileReader.h"

using namespace std;

int main(int argc, char* argv[])
{
	daemon(0, 0);

    try
    {
		if (argc != 1)
		{
			QString cause("Incorrect number of arguments.");
			throw ErrorException(cause, 1);
		}
		int caseId = atoi(argv[0]);

        ConnectionFileReader reader(QString("/home/zane/Documents/COS301/MainProject/Resources/connection.txt"));
        DatabaseConnection* conn = reader.getDatabaseConnection();

        string faceCascade = "/home/zane/Documents/COS301/MainProject/testFiles/haarcascade_frontalface_alt2.xml";
        Filter* faceDetect = new FaceDetectFilter(faceCascade);

		Filter* preProc = new PreProcessingFilter(140, 150);

        Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
		FacialFeatureRecognizer recognizer(model, 3600, conn, faceDetect, preProc);
		QString trainingFile("/home/zane/Documents/COS301/training.xml");
        recognizer.loadTrainingFromXML(trainingFile);
        recognizer.processCase(caseId);
    }
    catch (ErrorException e)
    {
        cout << e.toString().toStdString() << endl;
    }

    return 0;
}
