#ifndef PREPROCESSINGFILTERTEST_H
#define PREPROCESSINGFILTERTEST_H

#include <QtTest/QtTest>
#include "PreProcessingFilter.h"

class PreProcessingFilterTest : public QObject
{
    Q_OBJECT
    private slots:
        void greyScaleTest();
        void targetSizeTest();

};

#endif // PREPROCESSINGFILTERTEST_H
