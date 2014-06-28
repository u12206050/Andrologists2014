#ifndef FACEDETECTFILTERTEST_H
#define FACEDETECTFILTERTEST_H

#include <QtTest/QtTest>
#include "FaceDetectFilter.h"

class FaceDetectFilterTest : public QObject
{
    Q_OBJECT
    private slots:
        void filterTest();
};

#endif // FACEDETECTFILTERTEST_H
