#if !defined(_NSAMPLINGFILTER_H)
#define _NSAMPLINGFILTER_H

#include "SamplingFilter.h"

class NSamplingFilter : public SamplingFilter
{
private:
	int n;
public:
	~NSamplingFilter();
	virtual ImageData* filter(ImageData* image) = 0;
};

#endif  //_NSAMPLINGFILTER_H