#if !defined(_PREPROCESSINGFILTER_H)
#define _PREPROCESSINGFILTER_H

#include "opencv2/opencv.hpp"
#include "Filter.h"

using namespace cv;

/*const double DESIRED_LEFT_EYE_X = 0.16;
const double DESIRED_LEFT_EYE_Y = 0.14;
const double FACE_ELLIPSE_CY = 0.40;
const double FACE_ELLIPSE_W = 0.50;
const double FACE_ELLIPSE_H = 0.80;*/

class PreProcessingFilter : public Filter
{
    public:
		PreProcessingFilter(int targetWidth, int targetHeight);
        ~PreProcessingFilter();
        ImageData* filter(ImageData* image);

    private:
        void equalizeLeftAndRightHalves(Mat &faceImg);
		Mat getPreprocessedFace(Mat &srcImg, int targetWidth, int targetHeight, bool doLeftAndRightSeparately);
        int targetWidth;
        int targetHeight;
};

#endif  //_PREPROCESSINGFILTER_H
