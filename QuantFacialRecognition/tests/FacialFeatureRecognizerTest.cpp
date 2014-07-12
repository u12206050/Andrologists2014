#include "FacialFeatureRecognizerTest.h"

void FacialFeatureRecognizerTest::getSimilarFacesTest()
{
    Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
    FacialFeatureRecognizer recognizer(model, 920);
    QString trainingFile("../../testFiles/training.xml");
    recognizer.loadTrainingFromXML(trainingFile);

    GetSimilarFacesRequest* request = new GetSimilarFacesRequest;
    request->face = imread("../../testFiles/sameFace1", CV_LOAD_IMAGE_UNCHANGED);

    request->facesToCompareWith.push_back("../../testFiles/sameFace11");
    request->facesToCompareWith.push_back("../../testFiles/sameFace111");
    request->facesToCompareWith.push_back("../../testFiles/sameFace2");
    request->facesToCompareWith.push_back("../../testFiles/sameFace3");

    GetSimilarFacesResponse* response = recognizer.getSimilarFaces(request);

    QVERIFY(2 == response->similarFaces.size());
    SimilarFace* sFace = response->similarFaces[0];
    SimilarFace* sFace2 = response->similarFaces[1];
    Mat sameFace11 = imread("../../testFiles/sameFace11", CV_LOAD_IMAGE_UNCHANGED);
    Mat sameFace111 = imread("../../testFiles/sameFace111", CV_LOAD_IMAGE_UNCHANGED);
    QVERIFY(0 == norm(sFace->frame, sameFace11, NORM_L2));
    QVERIFY(0 == norm(sFace2->frame, sameFace111, NORM_L2));
}
