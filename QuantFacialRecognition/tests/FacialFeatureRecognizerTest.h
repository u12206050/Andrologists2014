#ifndef FACIALFEATURERECOGNIZERTEST_H
#define FACIALFEATURERECOGNIZERTEST_H

#include <QtTest/QtTest>
#include "FacialFeatureRecognizer.h"

class FacialFeatureRecognizerTest : public QObject
{
    Q_OBJECT
    private slots:
		void compareSimilarFacesTest();
		void compareNormalSmileSimilarFacesTest();
		void compareNormalFrownSimilarFacesTest();
		void compareSmileFrownSimilarFacesTest();
		void compareDifferentFacesTest();
};

#endif // FACIALFEATURERECOGNIZERTEST_H
