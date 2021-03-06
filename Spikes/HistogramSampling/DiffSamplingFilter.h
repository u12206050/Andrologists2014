#if !defined(_DIFFSAMPLINGFILTER_H)
#define _DIFFSAMPLINGFILTER_H

#include "SamplingFilter.h"
#include "ImageData.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class DiffSamplingFilter : public SamplingFilter
{
    public:
        DiffSamplingFilter(float thresholdValue);
        ~DiffSamplingFilter();
        ImageData* filter(ImageData* image);
    private:
        float thresholdValue;
        ImageData* prevImage;
};

#endif  //_DIFFSAMPLINGFILTER_H
