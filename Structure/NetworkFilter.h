#ifndef NETWORK_FILTER_H
#define NETWORK_FILTER_H

#include "Filter.h"

class NetworkFilter : public Filter
{
	public:
		virtual Mat filter(Mat image);
		virtual ~NetworkFilter();
	
	protected:
	
	private:
	
};

#endif
