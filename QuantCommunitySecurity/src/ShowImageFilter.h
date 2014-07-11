#ifndef SHOWIMAGEFILTER_H
#define SHOWIMAGEFILTER_H

#include "Filter.h"

#include <opencv2/highgui/highgui.hpp>
#include <QString>

using namespace cv;

class ShowImageFilter : public Filter
{
    public:
        ShowImageFilter(QString& windowName);
        ImageData* filter(ImageData* image);

    private:
        QString windowName;
};

#endif // SHOWIMAGEFILTER_H
