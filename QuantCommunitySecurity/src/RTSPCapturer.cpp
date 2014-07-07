#include "RTSPCapturer.h"

RTSPCapturer::RTSPCapturer(QString& videoLocation)
{
    if(!capturer.open(videoLocation.toStdString()))
    {
        throw Exception();
    }
}

RTSPCapturer::~RTSPCapturer()
{
}

ImageData* RTSPCapturer::getNextImage()
{
    ImageData* newImage = new ImageData;

    if(!capturer.read(newImage->image))
    {
        return NULL;
    }
    waitKey(1);

    QDate cd = QDate::currentDate();
    QTime ct = QTime::currentTime();

    newImage->timestamp.setDate(cd);
    newImage->timestamp.setTime(ct);

    return newImage;
}
