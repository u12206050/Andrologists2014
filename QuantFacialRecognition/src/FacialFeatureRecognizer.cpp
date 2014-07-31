#include "FacialFeatureRecognizer.h"

FacialFeatureRecognizer::FacialFeatureRecognizer(Ptr<FaceRecognizer> recognizer)
{
    this->recognizer = recognizer;
}

void FacialFeatureRecognizer::loadTrainingFromXML(QString& filename)
{
	recognizer->load(filename.toStdString());
}

double FacialFeatureRecognizer::compareFaces(Mat& face1, Mat& face2)
{

	Mat eigenVectors = recognizer->getMat("eigenvectors");
	Mat mean = recognizer->getMat("mean");

	Mat proj = subspaceProject(eigenVectors, mean, face1.reshape(1,1));
	Mat proj2 = subspaceProject(eigenVectors, mean, face2.reshape(1,1));

	return norm(proj, proj2, NORM_L2);
}

