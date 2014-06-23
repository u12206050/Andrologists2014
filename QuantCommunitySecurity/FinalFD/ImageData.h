#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include "opencv2/core/core.hpp"
#include <QDateTime>
using namespace cv;

class ImageData
{
public:
    Mat image;
    vector<Mat> faces;
    QDateTime timestamp;
};

#endif // IMAGEDATA_H
