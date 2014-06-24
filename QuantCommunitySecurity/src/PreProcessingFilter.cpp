#include "PreProcessingFilter.h"

PreProcessingFilter::~PreProcessingFilter()
{
    /*IplImage *imageGrey;
    if (imageSrc->nChannels == 3) {
        imageGrey = cvCreateImage( cvGetSize(imageSrc), IPL_DEPTH_8U, 1 );
        // Convert from RGB (actually it is BGR) to Greyscale.
        cvCvtColor( imageSrc, imageGrey, CV_BGR2GRAY );
    }
    else {
        // Just use the input image, since it is already Greyscale.
        imageGrey = imageSrc;
    }

    // Resize the image to be a consistent size, even if the aspect ratio changes.
    IplImage *imageProcessed;
    imageProcessed = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
    // Make the image a fixed size.
    // CV_INTER_CUBIC or CV_INTER_LINEAR is good for enlarging, and
    // CV_INTER_AREA is good for shrinking / decimation, but bad at enlarging.
    cvResize(imageGrey, imageProcessed, CV_INTER_LINEAR);

    // Give the image a standard brightness and contrast.
    cvEqualizeHist(imageProcessed, imageProcessed);



    if (imageGrey)
        cvReleaseImage(&imageGrey);
    if (imageProcessed)
        cvReleaseImage(&imageProcessed);*/
}

ImageData* PreProcessingFilter::filter(ImageData* image)
{
    return NULL;
}
