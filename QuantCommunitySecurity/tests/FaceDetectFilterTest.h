#ifndef FACEDETECTFILTERTEST_H
#define FACEDETECTFILTERTEST_H

#include <QtTest/QtTest>
#include "FaceDetectFilter.h"
#include "opencv2/opencv.hpp"

using namespace cv;

class FaceDetectFilterTest : public QObject
{
    Q_OBJECT
    private slots:
        void filterTest();
};

#endif // FACEDETECTFILTERTEST_H
