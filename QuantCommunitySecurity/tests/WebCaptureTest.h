#ifndef WEBCAPTURETEST_H
#define WEBCAPTURETEST_H

#include "WebCamCapturer.h"
#include <QtTest/QtTest>

class WebCaptureTest : public QObject
{
    Q_OBJECT
    private slots:
        void getNextImageTest();
};

#endif // WEBCAPTURETEST_H
