#include "RTSPCapturer.h"

RTSPCapturer::RTSPCapturer(char* Url)
{
    if(!vcap.open(Url)) {
            cout << "Error opening video stream or file" << endl;
            throw Exception();
        }

    data = new ImageData();
}

RTSPCapturer::~RTSPCapturer()
{
    vcap.~VideoCapture();
    delete data;
}

ImageData* RTSPCapturer::getNextImage()
{
    Mat image;

    if(!vcap.read(image))
    {
        cout << "No frame" << endl;
        return NULL;
    }

    data->image = image;

    QDate cd = QDate::currentDate();
    QTime ct = QTime::currentTime();

    data->timestamp.setDate(cd);
    data->timestamp.setTime(ct);

    return data;
}
