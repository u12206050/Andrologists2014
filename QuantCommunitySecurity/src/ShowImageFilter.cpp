#include "ShowImageFilter.h"

ShowImageFilter::ShowImageFilter(QString& windowName)
{
    this->windowName = windowName;
}

ImageData* ShowImageFilter::filter(ImageData* image)
{
    imshow(windowName.toStdString(), image->image);
    return image;
}
