#include "DiffSamplingFilter.h"

DiffSamplingFilter::DiffSamplingFilter(float thresholdValue)
{
    this->thresholdValue = thresholdValue;
    prevImage = NULL;
}

DiffSamplingFilter::~DiffSamplingFilter()
{

}

ImageData* DiffSamplingFilter::filter(ImageData* image)
{
    if(prevImage == NULL)
    {
        prevImage = image;
        return image;
    }

    Mat prev;
    Mat current;

    cvtColor(prevImage->image, prev, COLOR_BGR2HSV);
    cvtColor(image->image, current, COLOR_BGR2HSV);

    int h_bins = 50;
    int s_bins = 60;
    int histSize[] = {h_bins, s_bins};

    float h_ranges[] = {0, 180};
    float s_ranges[] = {0, 256};

    const float* ranges[] = {h_ranges, s_ranges};

    int channels[] = {0, 1};

    MatND prevHist;
    MatND currentHist;

    calcHist(&prev, 1, channels, Mat(), prevHist, 2, histSize, ranges, true, false);
    normalize(prevHist, prevHist, 0, 1, NORM_MINMAX, -1, Mat());

    calcHist(&current, 1, channels, Mat(), currentHist, 2, histSize, ranges, true, false);
    normalize(prevHist, prevHist, 0, 1, NORM_MINMAX, -1, Mat());

    double comparisonValue = compareHist(prevHist, currentHist, CV_COMP_BHATTACHARYYA);
    prevImage = image;

    if (comparisonValue > thresholdValue)
    {
        return image;
    }

    return NULL;
}
