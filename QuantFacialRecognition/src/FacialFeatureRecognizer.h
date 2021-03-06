#if !defined(_FACIALFEATURERECOGNIZER_H)
#define _FACIALFEATURERECOGNIZER_H

#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <QString>
#include "DatabaseReader.h"
#include "PreProcessingFilter.h"
#include "FaceDetectFilter.h"
#include "ErrorException.h"
#include "CaseManager.h"
#include "DatabaseConnection.h"
#include <QtSql>

using namespace cv;

class FacialFeatureRecognizer
{
    public:
        FacialFeatureRecognizer(Ptr<FaceRecognizer> recognizer, double threshold, DatabaseConnection* databaseConnection, Filter* faceDetectFilter, Filter* preProcessingFilter);
		double compareFaces(Mat& face1, Mat& face2);
        void loadTrainingFromXML(QString& filename);
        void processCase(int caseId);

    private:
        Ptr<FaceRecognizer> recognizer;
        double threshold;
        DatabaseConnection* databaseConnection;
        Filter* faceDetectFilter;
        Filter* preProcessingFilter;

        float scaleToPercentage(double unscaledValue);


};

#endif  //_FACIALFEATURERECOGNIZER_H
