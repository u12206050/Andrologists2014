#if !defined(_FACIALFEATURERECOGNIZER_H)
#define _FACIALFEATURERECOGNIZER_H

#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "GetSimilarFacesRequest.h"
#include "GetSimilarFacesResponse.h"

class FacialFeatureRecognizer
{
    public:
        FacialFeatureRecognizer(Ptr<FaceRecognizer> recognizer, double threshold);
        GetSimilarFacesResponse* getSimilarFaces(GetSimilarFacesRequest* request);
        void loadTrainingFromXML(String filename);
        void saveTrainingToXML(String filename);
        void train();

    private:
        double threshold;
        Ptr<FaceRecognizer> recognizer;
        double compareFaces(Mat& face1, Mat& face2);
};

#endif  //_FACIALFEATURERECOGNIZER_H
