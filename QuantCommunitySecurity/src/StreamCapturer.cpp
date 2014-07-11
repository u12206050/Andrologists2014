#include "StreamCapturer.h"

StreamCapturer::StreamCapturer(QString& videoLocation)
{
    if(!capturer.open(videoLocation.toStdString()))
    {
        throw Exception();
    }
}

StreamCapturer::StreamCapturer(int deviceId)
{
    if(!capturer.open(deviceId))
    {
        throw Exception();
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
        return NULL;
    }
    waitKey(1);

    QDateTime currentTime;

    newImage->timestamp = currentTime.currentMSecsSinceEpoch();

    return newImage;
}
