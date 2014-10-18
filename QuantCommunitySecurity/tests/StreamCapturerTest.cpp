#include "StreamCapturerTest.h"

void StreamCapturerTest::getNextImageTest()
{
    QString location("/home/zane/video.mjpg");
	StreamCapturer* capturer = new StreamCapturer(location);
	ImageData* data = capturer->getNextImage();
	QVERIFY(data->timestamp > 0);
	QVERIFY(data->image.rows > 0);
	QVERIFY(data->image.cols > 0);
}
