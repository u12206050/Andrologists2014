#if !defined(_DIFFSAMPLINGFILTER_H)
#define _DIFFSAMPLINGFILTER_H

#include "SamplingFilter.h"

class DiffSamplingFilter : public SamplingFilter
{
public:
	DiffSampling(float percentage);
	~DiffSamplingFilter();
	ImageData* filter(ImageData* image);
	ImageData* filter(ImageData* image);
	ImageData* filter(ImageData* image);
private:
	float percentage;
};

#endif  //_DIFFSAMPLINGFILTER_H
