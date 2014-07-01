#if !defined(_NSAMPLINGFILTER_H)
#define _NSAMPLINGFILTER_H

#include "SamplingFilter.h"
#include "ImageData.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
class NSamplingFilter : public SamplingFilter
{
private:
	int n;
	int counter;
	
public:
	NSamplingFilter(int num);
	~NSamplingFilter();
     ImageData* filter(ImageData* image);
};

#endif  //_NSAMPLINGFILTER_H
