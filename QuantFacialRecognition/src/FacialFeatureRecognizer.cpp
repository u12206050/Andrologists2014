#include "FacialFeatureRecognizer.h"

FacialFeatureRecognizer::FacialFeatureRecognizer(Ptr<FaceRecognizer> recognizer, double threshold)
{
    this->recognizer = recognizer;
    this->threshold = threshold;
}

void FacialFeatureRecognizer::loadTrainingFromXML(QString& filename)
{
    recognizer->load(filename.toStdString());
}

void FacialFeatureRecognizer::processCase(int caseId)
{
    DatabaseReader dbReader();
    QString filename = dbReader.getOriginalImageFilename(caseId);
    Mat imageTaken = imread(filename.toStdString(), CV_LOAD_IMAGE_UNCHANGED);
    ImageData* imageData = new ImageData();
    imageData->image = imageTaken;
    Filter* faceDetect = new FaceDetectFilter();
    Filter* preProcessing = new PreProcessingFilter();
    imageData = faceDetect->filter(imageData);
    if (imageData->faces.size() == 0)
    {
        QString cause("No face in image.");
        throw ErrorException(cause, 0);
    }
    imageData = preProcessing->filter(imageData);

    GetFaceDetailsResponse* response = dbReader.getAllFaceFilenames();
    vector<QString> faceFilenames = response->faceFilnames;
    vector<int> faceIds = response->ids;
    DatabasePersister dbPersister();

    for(int i = 0; i < faceNames.size(); i++)
    {
        Mat temp = imread(faceNames[i].toStdString(), CV_LOAD_IMAGE_UNCHANGED);
        double percentageMatch = compareFaces(imageData->faces[0], temp);
        if (percentageMatch <= threshold)
        {
            dbPersister.updateCaseStatus(caseId, ids[i], percentageMatch);
        }
    }

}

double FacialFeatureRecognizer::compareFaces(Mat& face1, Mat& face2)
{

	Mat eigenVectors = recognizer->getMat("eigenvectors");
	Mat mean = recognizer->getMat("mean");

	Mat proj = subspaceProject(eigenVectors, mean, face1.reshape(1,1));
	Mat proj2 = subspaceProject(eigenVectors, mean, face2.reshape(1,1));

	return norm(proj, proj2, NORM_L2);
}

