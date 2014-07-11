#include "FacialFeatureRecognizer.h"

FacialFeatureRecognizer::FacialFeatureRecognizer(Ptr<FaceRecognizer> recognizer, double threshold)
{
    this->recognizer = recognizer;
    this->threshold = threshold;
}

GetSimilarFacesResponse* FacialFeatureRecognizer::getSimilarFaces(GetSimilarFacesRequest* request)
{
    GetSimilarFacesResponse* response = new GetSimilarFacesResponse();
    for (unsigned int i = 0; i < request->facesToCompareWith.size(); i++)
    {
        Mat faceToCompare = imread(request->facesToCompareWith[i], CV_LOAD_IMAGE_UNCHANGED);
        double distance = compareFaces(request->face, faceToCompare);
        if (distance <= threshold)
        {
            SimilarFace* similarFace = new SimilarFace();
            similarFace->distance = distance;
            similarFace->timestamp = request->timestamps[i];
            //similarFace->frame =
        }
    }
    return response;
}

void FacialFeatureRecognizer::loadTrainingFromXML(String filename)
{
    recognizer->load(filename);
}

void FacialFeatureRecognizer::saveTrainingToXML(String filename)
{
    recognizer->save(filename);
}

void FacialFeatureRecognizer::train()
{

}

double FacialFeatureRecognizer::compareFaces(Mat& face1, Mat& face2)
{

    Mat proj = subspaceProject(recognizer->getMat("eigenvectors"), recognizer->getMat("mean"), face1.reshape(1,1));
    Mat proj2 = subspaceProject(recognizer->getMat("eigenvectors"), recognizer->getMat("mean"), face2.reshape(1,1));

    double distance = norm(proj, proj2, NORM_L2);
    return distance;
}

