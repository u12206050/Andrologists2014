#ifndef FACE_DETECT_FILTER_H
#define FACE_DETECT_FILTER_H

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
        FaceDetectFilter(string faceCascadeFilename, string faceCascadeSecondOpinionFilename = "");
        ~FaceDetectFilter();
        virtual ImageData* filter(ImageData* image);

    private:
        CascadeClassifier faceCascade;
        CascadeClassifier secondOpinion;
        bool useSecondOpinion;
};

#endif
