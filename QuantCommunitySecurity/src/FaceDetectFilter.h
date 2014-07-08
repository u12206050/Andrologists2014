#ifndef FACEDETECTFILTER_H
#define FACEDETECTFILTER_H

#include "Filter.h"
#include "ImageData.h"

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

class FaceDetectFilter : public Filter
{
    public:
        FaceDetectFilter(CascadeClassifier& faceCascade, CascadeClassifier& faceCascadeSecondOpinion);
        ~FaceDetectFilter();
        virtual ImageData* filter(ImageData* image);

    private:
        CascadeClassifier faceCascade;
        CascadeClassifier secondOpinion;
};

#endif // FACEDETECTFILTER_H
