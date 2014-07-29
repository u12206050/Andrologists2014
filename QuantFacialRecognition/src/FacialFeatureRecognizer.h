#if !defined(_FACIALFEATURERECOGNIZER_H)
#define _FACIALFEATURERECOGNIZER_H

#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <QString>

using namespace cv;

class FacialFeatureRecognizer
{
    public:
		FacialFeatureRecognizer(Ptr<FaceRecognizer> recognizer);
		double compareFaces(Mat& face1, Mat& face2);
        void loadTrainingFromXML(QString& filename);

    private:
        Ptr<FaceRecognizer> recognizer;

};

#endif  //_FACIALFEATURERECOGNIZER_H
