#include "ImageData.h"

ImageData::ImageData()
{

}

ImageData::ImageData(Mat image, QDateTime timestamp)
{
    this->image = image;
    this->timestamp = timestamp;
}

void ImageData::addFace(Mat face)
{
    faces.push_back(face);
}
