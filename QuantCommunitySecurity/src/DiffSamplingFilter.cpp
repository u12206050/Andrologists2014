#include "DiffSamplingFilter.h"
using namespace std;
DiffSamplingFilter::DiffSamplingFilter(float per)
{
	percentage = per;
    //
 prevImage = new ImageData();
 prevImage = NULL;
}

DiffSamplingFilter::~DiffSamplingFilter()
{

}

double DiffSamplingFilter::getScore()
{
	return totscore;
}

ImageData* DiffSamplingFilter::filter(ImageData* image)
{

	//if more than percentage differs, return the image
    if(prevImage == NULL)
	{
        prevImage = image;

	}
    else
    {
				//previous image. Calculate histogram.

                Mat src_mat = prevImage->image;
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
				totscore = score;

				prevImage = image; //save the image

				if(score < percentage) //similar
				{	
					return image;
				}
				else
				{
                    return NULL;
				}

    }
    return NULL;

	
}
