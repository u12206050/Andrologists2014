#if !defined(_DIFFSAMPLINGFILTER_H)
#define _DIFFSAMPLINGFILTER_H

#include "SamplingFilter.h"

class DiffSamplingFilter : public SamplingFilter
{
private:
	float percentage; 
public:
	~DiffSamplingFilter();
	virtual ImageData* filter(ImageData* image) = 0;
};

#endif  //_DIFFSAMPLINGFILTER_H