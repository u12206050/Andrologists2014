#include "ImageData.h"

ImageData::ImageData()
{

}

/*ImageData::ImageData(Mat image, qint64 timestamp)
{
    this->image = image;
    this->timestamp = timestamp;
}*/

void ImageData::addFace(Mat face)
{
    faces.push_back(face);
}
