#if !defined(_PREPROCESSINGFILTER_H)
#define _PREPROCESSINGFILTER_H

#include "opencv2/opencv.hpp"
#include "Filter.h"

using namespace cv;

const double DESIRED_LEFT_EYE_X = 0.16;
const double DESIRED_LEFT_EYE_Y = 0.14;
const double FACE_ELLIPSE_CY = 0.40;
const double FACE_ELLIPSE_W = 0.50;
const double FACE_ELLIPSE_H = 0.80;

class PreProcessingFilter : public Filter
{
    public:
        PreProcessingFilter(int targetWidth, int targetHeight, CascadeClassifier& eyeCascade1, CascadeClassifier& eyeCascade2);
        ~PreProcessingFilter();
        ImageData* filter(ImageData* image);

    private:
        void detectObjectsCustom(const Mat &image, CascadeClassifier &cascade, vector<Rect> &objects, int scaledWidth, int flags, Size minFeatureSize, float searchScaleFactor, int minNeighbors);
        void detectLargestObject(const Mat &image, CascadeClassifier &cascade, Rect &largestObject, int scaledWidth);
        void detectBothEyes(const Mat &face, CascadeClassifier &eyeCascade1, CascadeClassifier &eyeCascade2, Point &leftEye, Point &rightEye, Rect *searchedLeftEye, Rect *searchedRightEye);
        void equalizeLeftAndRightHalves(Mat &faceImg);
        Mat getPreprocessedFace(Mat &srcImg, CascadeClassifier &eyeCascade1, CascadeClassifier &eyeCascade2, bool doLeftAndRightSeparately, Point *storeLeftEye, Point *storeRightEye, Rect *searchedLeftEye, Rect *searchedRightEye);
        int targetWidth;
        int targetHeight;
        CascadeClassifier eyeCascade1;
        CascadeClassifier eyeCascade2;
};

#endif  //_PREPROCESSINGFILTER_H
