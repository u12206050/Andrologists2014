#include "StreamCapturer.h"

#include "iostream"

using namespace std;

StreamCapturer::StreamCapturer(QString& videoLocation)
{
	if(!capturer.open(videoLocation.toStdString()))
    {
		QString cause("cannot open stream.");
		throw ErrorException(cause, 0);
    }
}

StreamCapturer::StreamCapturer(int deviceId)
{
    if(!capturer.open(deviceId))
    {
		QString cause("cannot open device.");
		throw ErrorException(cause, 1);
    }
}

StreamCapturer::~StreamCapturer()
{
}

ImageData* StreamCapturer::getNextImage()
{
    ImageData* newImage = new ImageData;

    if(!capturer.read(newImage->image))
    {
		QString cause("no frame to read.");
		throw ErrorException(cause, 2);
    }
    waitKey(1);

    QDateTime currentTime;

    newImage->timestamp = currentTime.currentMSecsSinceEpoch();

    return newImage;
}
