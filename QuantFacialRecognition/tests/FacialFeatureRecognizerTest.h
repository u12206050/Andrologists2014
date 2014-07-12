#ifndef FACIALFEATURERECOGNIZERTEST_H
#define FACIALFEATURERECOGNIZERTEST_H

#include <QtTest/QtTest>
#include "FacialFeatureRecognizer.h"

class FacialFeatureRecognizerTest : public QObject
{
    Q_OBJECT
    private slots:
        void getSimilarFacesTest();
};

#endif // FACIALFEATURERECOGNIZERTEST_H
