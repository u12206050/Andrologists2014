#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include "opencv2/core/core.hpp"

using namespace cv;

class ImageData
{
public:
    Mat image;
    vector<Mat> faces;
};

#endif // IMAGEDATA_H
