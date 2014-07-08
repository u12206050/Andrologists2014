#ifndef NSAMPLINGFILTERTEST_H
#define NSAMPLINGFILTERTEST_H

#include <QtTest/QtTest>
#include "NSamplingFilter.h"

class NSamplingFilterTest : public QObject
{
    Q_OBJECT
    private slots:
        void filterTest();
};
#endif // NSAMPLINGFILTERTEST_H
