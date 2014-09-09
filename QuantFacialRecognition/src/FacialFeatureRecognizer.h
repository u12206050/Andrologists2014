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
#include "DatabasePersister.h"

using namespace cv;

class FacialFeatureRecognizer
{
    public:
		FacialFeatureRecognizer(Ptr<FaceRecognizer> recognizer);
		double compareFaces(Mat& face1, Mat& face2);
        void loadTrainingFromXML(QString& filename);
        void processCase(int caseId);

    private:
        Ptr<FaceRecognizer> recognizer;
        double threshold;

};

#endif  //_FACIALFEATURERECOGNIZER_H
