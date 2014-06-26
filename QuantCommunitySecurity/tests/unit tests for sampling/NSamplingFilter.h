#if !defined(_NSAMPLINGFILTER_H)
#define _NSAMPLINGFILTER_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
class NSamplingFilter
{
private:
	int n;
	int counter;
	
public:
	NSamplingFilter(int number);
	~NSamplingFilter();
	IplImage* filter(IplImage* image);
};

#endif  //_NSAMPLINGFILTER_H