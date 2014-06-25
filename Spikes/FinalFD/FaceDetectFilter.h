#ifndef FACEDETECTFILTER_H
#define FACEDETECTFILTER_H

#include "Filter.h"
#include "ImageData.h"

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;

class FaceDetectFilter : public Filter
{
private:
    CascadeClassifier face_cascade;
public:
    FaceDetectFilter();
    ~FaceDetectFilter();
    virtual ImageData* filter(ImageData* image);
};

#endif // FACEDETECTFILTER_H
