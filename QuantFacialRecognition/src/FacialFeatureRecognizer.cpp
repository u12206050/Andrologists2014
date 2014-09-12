#include "FacialFeatureRecognizer.h"

FacialFeatureRecognizer::FacialFeatureRecognizer(Ptr<FaceRecognizer> recognizer, double threshold, DatabaseConnection* databaseConnection, Filter* faceDetectFilter, Filter* preProcessingFilter)
{
    this->recognizer = recognizer;
    this->threshold = threshold;
    this->faceDetectFilter = faceDetectFilter;
    this->preProcessingFilter = preProcessingFilter;
    this->databaseConnection = databaseConnection;
}

void FacialFeatureRecognizer::loadTrainingFromXML(QString& filename)
{
    recognizer->load(filename.toStdString());
}

void FacialFeatureRecognizer::processCase(int caseId)
{
    DatabaseReader dbReader(databaseConnection);
    CaseManager* caseManager = new CaseManager(databaseConnection, caseId);
    QString filename = dbReader.getOriginalImageFilename(caseManager->getCaseId());
    Mat imageTaken = imread(filename.toStdString(), CV_LOAD_IMAGE_UNCHANGED);
    ImageData* imageData = new ImageData();
    imageData->image = imageTaken;
    imageData = faceDetectFilter->filter(imageData);
    if (imageData->faces.size() == 0)
    {
        QString cause("No face in image.");
        throw ErrorException(cause, 0);
    }
    imageData = preProcessingFilter->filter(imageData);

    GetFaceDetailsResponse* response = dbReader.getAllFaceFilenamesAndIds();
    vector<QString> faceFilenames = response->faceFilnames;
    vector<int> faceIds = response->ids;

    caseManager->instialiseCaseComparisons(faceIds.size());

    for (unsigned int i = 0; i < faceFilenames.size(); i++)
    {
        Mat temp = imread(faceFilenames[i].toStdString(), CV_LOAD_IMAGE_UNCHANGED);
        double percentageMatch = compareFaces(imageData->faces[0], temp);
        cout << "compared face: " << percentageMatch << endl;
        caseManager->updateProgress();
        if (percentageMatch <= threshold)
        {
            caseManager->updateCaseStatus(faceIds[i], percentageMatch);
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

