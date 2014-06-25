#include "PreProcessingFilter.h"

PreProcessingFilter::PreProcessingFilter(int targetWidth, int targetHeight)
{
    this->targetWidth = targetWidth;
    this->targetHeight = targetHeight;
}

PreProcessingFilter::~PreProcessingFilter()
{

}

ImageData* PreProcessingFilter::filter(ImageData* image)
{
    for (unsigned int i = 0; i < image->faces.size(); i++)
    {
        preProcessImage(image->faces[i]);
    }
    return image;
}

void PreProcessingFilter::preProcessImage(Mat& image)
{
    resize(image, image, Size(targetWidth, targetHeight), 1.0, 1.0, INTER_CUBIC);
    cvtColor(image, image, CV_BGR2GRAY);
    equalizeHist(image, image);
}
