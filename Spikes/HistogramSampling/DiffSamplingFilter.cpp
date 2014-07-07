#include "DiffSamplingFilter.h"

#include <iostream>
using namespace std;

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
    int histSize[] = { h_bins, s_bins };

    float h_ranges[] = { 0, 180 };
    float s_ranges[] = { 0, 256 };

    const float* ranges[] = { h_ranges, s_ranges };

    int channels[] = { 0, 1 };
    
    MatND prevHist;
    MatND currentHist;
    
    calcHist(&prev, 1, channels, Mat(), prevHist, 2, histSize, ranges, true, false);
    normalize(prevHist, prevHist, 0, 1, NORM_MINMAX, -1, Mat());
    
    calcHist(&current, 1, channels, Mat(), currentHist, 2, histSize, ranges, true, false);
    normalize(prevHist, prevHist, 0, 1, NORM_MINMAX, -1, Mat());
    
    double comparisonValue = compareHist(prevHist, currentHist, CV_COMP_BHATTACHARYYA);
    prevImage = image;
    
    cout << comparisonValue << endl;
    
    if (comparisonValue > thresholdValue)
    {
		return image;
	}
    
    return NULL;


    /*Mat src_mat = prevImage->image;
    Mat hsv_mat;
    cvtColor( src_mat, hsv_mat, CV_BGR2HSV );
    MatND HSV_histogram;
    int histSize[] = { 240, 240 };
    float h_ranges[] = { 0, 255 };
    float s_ranges[] = { 0, 180 };
    const float* ranges[] = { h_ranges, s_ranges };
    int channels[] = { 0, 1 };
    calcHist( &hsv_mat, 1, channels, Mat(), HSV_histogram, 2, histSize, ranges, true, false );
    normalize( HSV_histogram, HSV_histogram, 0, 1, NORM_MINMAX, -1, Mat() );

    //new image. Calculate histogram
    Mat src_mat2 = image->image;
    Mat hsv_mat2;
    cvtColor( src_mat2, hsv_mat2, CV_BGR2HSV );
    MatND HSV_histogram2;
    int histSize2[] = { 240, 240 };
    float h_ranges2[] = { 0, 255 };
    float s_ranges2[] = { 0, 180 };
    const float* ranges2[] = { h_ranges2, s_ranges2 };
    int channels2[] = { 0, 1 };
    calcHist( &hsv_mat2, 1, channels2, Mat(), HSV_histogram2, 2, histSize2, ranges2, true, false );
    normalize( HSV_histogram2, HSV_histogram2, 0, 1, NORM_MINMAX, -1, Mat() );


    //calculate the histogram difference
    double score = compareHist( HSV_histogram, HSV_histogram2, CV_COMP_BHATTACHARYYA ); //low score = good match, high score = bad match
    cout << score << endl;
    prevImage = image; //save the image

    if(score < thresholdValue) //similar
    {
        return image;
    }
    else
    {
        return NULL;
    }*/

}
