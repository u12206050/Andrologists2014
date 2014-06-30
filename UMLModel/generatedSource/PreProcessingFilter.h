#if !defined(_PREPROCESSINGFILTER_H)
#define _PREPROCESSINGFILTER_H

#include "Filter.h"

class PreProcessingFilter : public Filter
{
public:
	~PreProcessingFilter();
	ImageData* filter(ImageData* image);
	ImageData* filter(ImageData* image);
};

#endif  //_PREPROCESSINGFILTER_H
