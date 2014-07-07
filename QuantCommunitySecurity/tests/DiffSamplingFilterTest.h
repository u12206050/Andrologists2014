#ifndef DIFFSAMPLINGFILTERTEST_H
#define DIFFSAMPLINGFILTERTEST_H

#include <QtTest/QtTest>
#include "DiffSamplingFilter.h"

class DiffSamplingFilterTest : public QObject
{
    Q_OBJECT
    private slots:
        void filterTest();
};
#endif // DIFFSAMPLINGFILTERTEST_H
