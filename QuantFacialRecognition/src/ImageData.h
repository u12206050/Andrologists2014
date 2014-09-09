#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <QtGlobal>
#include "opencv2/core/core.hpp"

using namespace cv;

class ImageData
{
    public:
        ImageData();
        ImageData(Mat image, qint64 timestamp);
        void addFace(Mat face);
        Mat image;
        vector<Mat> faces;
        qint64 timestamp;
};

#endif
