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
		image->faces[i] = getPreprocessedFace(image->faces[i], targetWidth, targetHeight, true);
    }
    return image;
}

void PreProcessingFilter::equalizeLeftAndRightHalves(Mat &faceImg)
{
    int w = faceImg.cols;
    int h = faceImg.rows;

    Mat wholeFace;
    equalizeHist(faceImg, wholeFace);

    int midX = w/2;
    Mat leftSide = faceImg(Rect(0,0, midX,h));
    Mat rightSide = faceImg(Rect(midX,0, w-midX,h));
    equalizeHist(leftSide, leftSide);
    equalizeHist(rightSide, rightSide);

    for (int y=0; y<h; y++)
    {
        for (int x=0; x<w; x++)
        {
            int v;
            if (x < w/4)
            {
                v = leftSide.at<uchar>(y,x);
            }
            else if (x < w*2/4)
            {
                int lv = leftSide.at<uchar>(y,x);
                int wv = wholeFace.at<uchar>(y,x);
                float f = (x - w*1/4) / (float)(w*0.25f);
                v = cvRound((1.0f - f) * lv + (f) * wv);
            }
            else if (x < w*3/4)
            {
                int rv = rightSide.at<uchar>(y,x-midX);
                int wv = wholeFace.at<uchar>(y,x);
                float f = (x - w*2/4) / (float)(w*0.25f);
                v = cvRound((1.0f - f) * wv + (f) * rv);
            }
            else
            {
                v = rightSide.at<uchar>(y,x-midX);
            }
            faceImg.at<uchar>(y,x) = v;
        }
    }
}

Mat PreProcessingFilter::getPreprocessedFace(Mat &srcImg, int desiredFaceWidth, int desiredFaceHeight, bool doLeftAndRightSeparately)
{

    Mat faceImg = srcImg;
    Mat gray;
    if (faceImg.channels() == 3)
    {
        cvtColor(faceImg, gray, CV_BGR2GRAY);
    }
    else if (faceImg.channels() == 4)
    {
        cvtColor(faceImg, gray, CV_BGRA2GRAY);
    }
    else
    {
        gray = faceImg;
    }

	if (!doLeftAndRightSeparately)
	{
		equalizeHist(gray, gray);
	}
	else
	{
		equalizeLeftAndRightHalves(gray);
	}


	Size s(desiredFaceWidth, desiredFaceHeight);
	Mat dstImg;
	resize(gray, dstImg, s);

	return dstImg;
}
