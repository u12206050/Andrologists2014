#if !defined(_DIFFSAMPLINGFILTER_H)
#define _DIFFSAMPLINGFILTER_H


#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

class DiffSamplingFilter
{
private:
	float percentage; 
	IplImage* prevImage;
	double totscore;
public:
	DiffSamplingFilter(float per);
	~DiffSamplingFilter();
	IplImage* filter(IplImage* image);
	double getScore();
};

#endif  //_DIFFSAMPLINGFILTER_H