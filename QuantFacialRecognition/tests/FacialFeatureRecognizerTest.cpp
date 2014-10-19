#include "FacialFeatureRecognizerTest.h"

void FacialFeatureRecognizerTest::compareSimilarFacesTest()
{
    Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
	FacialFeatureRecognizer recognizer(model, 0, NULL, NULL, NULL);
	QString trainingFile("/home/zane/Documents/COS301/training.xml");
    recognizer.loadTrainingFromXML(trainingFile);

	Mat face1 = imread("../../testFiles/FaceRec/barack_normal.jpg", CV_LOAD_IMAGE_UNCHANGED);
	Mat face2 = imread("../../testFiles/FaceRec/barack_normal2.jpg", CV_LOAD_IMAGE_UNCHANGED);

	string faceCascade = "/home/zane/Documents/COS301/MainProject/testFiles/haarcascade_frontalface_alt2.xml";
	Filter* faceDetect = new FaceDetectFilter(faceCascade);
	Filter* preProc = new PreProcessingFilter(140, 150);

	ImageData* data1 = new ImageData(face1, 0);
	data1 = faceDetect->filter(data1);
	data1 = preProc->filter(data1);

	ImageData* data2 = new ImageData(face2, 0);
	data2 = faceDetect->filter(data2);
	data2 = preProc->filter(data2);

	double expected = 5800;
	double actual = recognizer.compareFaces(data1->faces[0], data2->faces[0]);

	QVERIFY(actual <= expected);
}

void FacialFeatureRecognizerTest::compareNormalSmileSimilarFacesTest()
{
	Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
    FacialFeatureRecognizer recognizer(model, 0, NULL, NULL, NULL);
	QString trainingFile("/home/zane/Documents/COS301/training.xml");
	recognizer.loadTrainingFromXML(trainingFile);

	Mat face1 = imread("../../testFiles/FaceRec/barack_normal.jpg", CV_LOAD_IMAGE_UNCHANGED);
	Mat face2 = imread("../../testFiles/FaceRec/barack_smile.jpg", CV_LOAD_IMAGE_UNCHANGED);

	string faceCascade = "/home/zane/Documents/COS301/MainProject/testFiles/haarcascade_frontalface_alt2.xml";
	Filter* faceDetect = new FaceDetectFilter(faceCascade);
	Filter* preProc = new PreProcessingFilter(140, 150);

	ImageData* data1 = new ImageData(face1, 0);
	data1 = faceDetect->filter(data1);
	data1 = preProc->filter(data1);

	ImageData* data2 = new ImageData(face2, 0);
	data2 = faceDetect->filter(data2);
	data2 = preProc->filter(data2);

	double expected = 5800;
	double actual = recognizer.compareFaces(data1->faces[0], data2->faces[0]);

	QVERIFY(actual <= expected);
}

void FacialFeatureRecognizerTest::compareNormalFrownSimilarFacesTest()
{
	Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
    FacialFeatureRecognizer recognizer(model, 0, NULL, NULL, NULL);
	QString trainingFile("/home/zane/Documents/COS301/training.xml");
	recognizer.loadTrainingFromXML(trainingFile);

	Mat face1 = imread("../../testFiles/FaceRec/barack_frown.jpg", CV_LOAD_IMAGE_UNCHANGED);
	Mat face2 = imread("../../testFiles/FaceRec/barack_normal2.jpg", CV_LOAD_IMAGE_UNCHANGED);
	string faceCascade = "/home/zane/Documents/COS301/MainProject/testFiles/haarcascade_frontalface_alt2.xml";
	Filter* faceDetect = new FaceDetectFilter(faceCascade);
	Filter* preProc = new PreProcessingFilter(140, 150);

	ImageData* data1 = new ImageData(face1, 0);
	data1 = faceDetect->filter(data1);
	data1 = preProc->filter(data1);

	ImageData* data2 = new ImageData(face2, 0);
	data2 = faceDetect->filter(data2);
	data2 = preProc->filter(data2);

	double expected = 6400;
	double actual = recognizer.compareFaces(data1->faces[0], data2->faces[0]);

	QVERIFY(actual <= expected);
}

void FacialFeatureRecognizerTest::compareSmileFrownSimilarFacesTest()
{
	Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
    FacialFeatureRecognizer recognizer(model, 0, NULL, NULL, NULL);
	QString trainingFile("/home/zane/Documents/COS301/training.xml");
	recognizer.loadTrainingFromXML(trainingFile);

	Mat face1 = imread("../../testFiles/FaceRec/barack_smile.jpg", CV_LOAD_IMAGE_UNCHANGED);
	Mat face2 = imread("../../testFiles/FaceRec/barack_frown.jpg", CV_LOAD_IMAGE_UNCHANGED);

	string faceCascade = "/home/zane/Documents/COS301/MainProject/testFiles/haarcascade_frontalface_alt2.xml";
	Filter* faceDetect = new FaceDetectFilter(faceCascade);
	Filter* preProc = new PreProcessingFilter(140, 150);

	ImageData* data1 = new ImageData(face1, 0);
	data1 = faceDetect->filter(data1);
	data1 = preProc->filter(data1);

	ImageData* data2 = new ImageData(face2, 0);
	data2 = faceDetect->filter(data2);
	data2 = preProc->filter(data2);

	double expected = 5800;
	double actual = recognizer.compareFaces(data1->faces[0], data2->faces[0]);

	QVERIFY(actual <= expected);
}

void FacialFeatureRecognizerTest::compareDifferentFacesTest()
{
	Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
    FacialFeatureRecognizer recognizer(model, 0, NULL, NULL, NULL);
	QString trainingFile("/home/zane/Documents/COS301/training.xml");
	recognizer.loadTrainingFromXML(trainingFile);

	Mat face1 = imread("../../testFiles/FaceRec/barack_normal.jpg", CV_LOAD_IMAGE_UNCHANGED);
	Mat face2 = imread("../../testFiles/FaceRec/george_normal.jpg", CV_LOAD_IMAGE_UNCHANGED);

	string faceCascade = "/home/zane/Documents/COS301/MainProject/testFiles/haarcascade_frontalface_alt2.xml";
	Filter* faceDetect = new FaceDetectFilter(faceCascade);
	Filter* preProc = new PreProcessingFilter(140, 150);

	ImageData* data1 = new ImageData(face1, 0);
	data1 = faceDetect->filter(data1);
	data1 = preProc->filter(data1);

	ImageData* data2 = new ImageData(face2, 0);
	data2 = faceDetect->filter(data2);
	data2 = preProc->filter(data2);

	double expected = 3000;
	double actual = recognizer.compareFaces(data1->faces[0], data2->faces[0]);

	QVERIFY(actual > expected);
}
