#if !defined(_PREPROCESSINGFILTER_H)
#define _PREPROCESSINGFILTER_H

#include "opencv2/imgproc/imgproc.hpp"
#include "Filter.h"

using namespace cv;

class PreProcessingFilter : public Filter
{
    public:
        PreProcessingFilter(int targetWidth, int targetHeight);
        ~PreProcessingFilter();
        ImageData* filter(ImageData* image);

    private:
        void preProcessImage(Mat& image);
        int targetWidth;
        int targetHeight;
};

#endif  //_PREPROCESSINGFILTER_H
