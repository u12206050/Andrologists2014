#include "FacialFeatureRecognizerTest.h"

void FacialFeatureRecognizerTest::compareSimilarFacesTest()
{
    Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
    FacialFeatureRecognizer recognizer(model, 0, NULL, NULL, NULL);
	QString trainingFile("../../testFiles/FaceRec/training.xml");
    recognizer.loadTrainingFromXML(trainingFile);

	Mat face1 = imread("../../testFiles/FaceRec/barack_normal_p.jpg", CV_LOAD_IMAGE_UNCHANGED);
	Mat face2 = imread("../../testFiles/FaceRec/barack_normal2_p.jpg", CV_LOAD_IMAGE_UNCHANGED);

	double expected = 920;
	double actual = recognizer.compareFaces(face1, face2);

	QVERIFY(actual <= expected);
}

void FacialFeatureRecognizerTest::compareNormalSmileSimilarFacesTest()
{
	Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
    FacialFeatureRecognizer recognizer(model, 0, NULL, NULL, NULL);
	QString trainingFile("../../testFiles/FaceRec/training.xml");
	recognizer.loadTrainingFromXML(trainingFile);

	Mat face1 = imread("../../testFiles/FaceRec/barack_normal_p.jpg", CV_LOAD_IMAGE_UNCHANGED);
	Mat face2 = imread("../../testFiles/FaceRec/barack_smile_p.jpg", CV_LOAD_IMAGE_UNCHANGED);

	double expected = 920;
	double actual = recognizer.compareFaces(face1, face2);

	QVERIFY(actual <= expected);
}

void FacialFeatureRecognizerTest::compareNormalFrownSimilarFacesTest()
{
	Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
    FacialFeatureRecognizer recognizer(model, 0, NULL, NULL, NULL);
	QString trainingFile("../../testFiles/FaceRec/training.xml");
	recognizer.loadTrainingFromXML(trainingFile);

	Mat face1 = imread("../../testFiles/FaceRec/barack_frown_p.jpg", CV_LOAD_IMAGE_UNCHANGED);
	Mat face2 = imread("../../testFiles/FaceRec/barack_normal2_p.jpg", CV_LOAD_IMAGE_UNCHANGED);

	double expected = 920;
	double actual = recognizer.compareFaces(face1, face2);

	QVERIFY(actual <= expected);
}

void FacialFeatureRecognizerTest::compareSmileFrownSimilarFacesTest()
{
	Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
    FacialFeatureRecognizer recognizer(model, 0, NULL, NULL, NULL);
	QString trainingFile("../../testFiles/FaceRec/training.xml");
	recognizer.loadTrainingFromXML(trainingFile);

	Mat face1 = imread("../../testFiles/FaceRec/barack_smile_p.jpg", CV_LOAD_IMAGE_UNCHANGED);
	Mat face2 = imread("../../testFiles/FaceRec/barack_frown_p.jpg", CV_LOAD_IMAGE_UNCHANGED);

	double expected = 920;
	double actual = recognizer.compareFaces(face1, face2);

	QVERIFY(actual <= expected);
}

void FacialFeatureRecognizerTest::compareDifferentFacesTest()
{
	Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
    FacialFeatureRecognizer recognizer(model, 0, NULL, NULL, NULL);
	QString trainingFile("../../testFiles/FaceRec/training.xml");
	recognizer.loadTrainingFromXML(trainingFile);

	Mat face1 = imread("../../testFiles/FaceRec/barack_normal_p.jpg", CV_LOAD_IMAGE_UNCHANGED);
	Mat face2 = imread("../../testFiles/FaceRec/george_normal_p.jpg", CV_LOAD_IMAGE_UNCHANGED);

	double expected = 920;
	double actual = recognizer.compareFaces(face1, face2);

	QVERIFY(actual > expected);
}
