#ifndef SAMPLING_FILTER_H
#define SAMPLING_FILTER_H

#include "Filter.h"

class SamplingFilter : public Filter
{
	public:
		virtual Mat filter(Mat image);
		virtual ~SamplingFilter();
	
	protected:
	
	private:
	
};

#endif
