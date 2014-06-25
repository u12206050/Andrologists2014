#if !defined(_DIFFSAMPLINGFILTER_H)
#define _DIFFSAMPLINGFILTER_H

#include "SamplingFilter.h"
#include "ImageData.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

class DiffSamplingFilter : public SamplingFilter
{
private:
	float percentage; 
	ImageData* prevImage = null;
public:
	~DiffSamplingFilter();
	virtual ImageData* filter(ImageData* image);
};

#endif  //_DIFFSAMPLINGFILTER_H