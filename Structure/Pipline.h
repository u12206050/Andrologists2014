#ifndef PIPELINE_H
#define PIPELINE_H

#include "Filter.h"
#include <vector>

using namespace std;

class Pipeline
{
	public:
		~Pipeline();
		void process(Mat image);
		void addFilter(Filter* filter);
	
	private:
		vector<Filter*> filters;
	
};

#endif
