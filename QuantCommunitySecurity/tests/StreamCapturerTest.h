#ifndef STREAMCAPTURERTEST_H
#define STREAMCAPTURERTEST_H

#include <QtTest/QtTest>
#include "StreamCapturer.h"

class StreamCapturerTest : public QObject
{
	Q_OBJECT
	private slots:
		void getNextImageTest();
};

#endif // STREAMCAPTURERTEST_H
