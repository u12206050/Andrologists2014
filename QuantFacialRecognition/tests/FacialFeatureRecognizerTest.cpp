#include "FacialFeatureRecognizerTest.h"

void FacialFeatureRecognizerTest::compareSimilarFacesTest()
{
    Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
	FacialFeatureRecognizer recognizer(model);
	QString trainingFile("../../testFiles/FaceRec/training.xml");
    recognizer.loadTrainingFromXML(trainingFile);

	Mat face1 = imread("../../testFiles/FaceRec/barack_normal_p.jpg");
	Mat face2 = imread("../../testFiles/FaceRec/barack_normal2_p.jpg");

	double expected = 920;
	double actual = recognizer.compareFaces(face1, face2);

	QVERIFY(actual <= expected);
}

void FacialFeatureRecognizerTest::compareNormalSmileSimilarFacesTest()
{
	Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
	FacialFeatureRecognizer recognizer(model);
	QString trainingFile("../../testFiles/FaceRec/training.xml");
	recognizer.loadTrainingFromXML(trainingFile);

	Mat face1 = imread("../../testFiles/FaceRec/barack_normal_p.jpg");
	Mat face2 = imread("../../testFiles/FaceRec/barack_smile_p.jpg");

	double expected = 920;
	double actual = recognizer.compareFaces(face1, face2);

	QVERIFY(actual <= expected);
}

void FacialFeatureRecognizerTest::compareNormalFrownSimilarFacesTest()
{
	Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
	FacialFeatureRecognizer recognizer(model);
	QString trainingFile("../../testFiles/FaceRec/training.xml");
	recognizer.loadTrainingFromXML(trainingFile);

	Mat face1 = imread("../../testFiles/FaceRec/barack_frown_p.jpg");
	Mat face2 = imread("../../testFiles/FaceRec/barack_normal2_p.jpg");

	double expected = 920;
	double actual = recognizer.compareFaces(face1, face2);

	QVERIFY(actual <= expected);
}

void FacialFeatureRecognizerTest::compareSmileFrownSimilarFacesTest()
{
	Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
	FacialFeatureRecognizer recognizer(model);
	QString trainingFile("../../testFiles/FaceRec/training.xml");
	recognizer.loadTrainingFromXML(trainingFile);

	Mat face1 = imread("../../testFiles/FaceRec/barack_smile_p.jpg");
	Mat face2 = imread("../../testFiles/FaceRec/barack_frown_p.jpg");

	double expected = 920;
	double actual = recognizer.compareFaces(face1, face2);

	QVERIFY(actual <= expected);
}

void FacialFeatureRecognizerTest::compareDifferentFacesTest()
{
	Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
	FacialFeatureRecognizer recognizer(model);
	QString trainingFile("../../testFiles/FaceRec/training.xml");
	recognizer.loadTrainingFromXML(trainingFile);

	Mat face1 = imread("../../testFiles/FaceRec/barack_normal_p.jpg");
	Mat face2 = imread("../../testFiles/FaceRec/george_normal_p.jpg");

	double expected = 920;
	double actual = recognizer.compareFaces(face1, face2);

	QVERIFY(actual > expected);
}
