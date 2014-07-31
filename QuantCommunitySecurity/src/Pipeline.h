#ifndef PIPELINE_H
#define PIPELINE_H

#include "Filter.h"
#include "Capturer.h"
#include "Persister.h"
#include "ImageData.h"
#include <vector>

using namespace std;

class Pipeline
{
    public:
        virtual ~Pipeline();
        int getNumberOfFilters();
        void attachFilter(Filter* filter);
        void attachFilters(vector<Filter*> filters);
        void attachCapturer(Capturer* capturer);
        void attachPersister(Persister* persister);
        Capturer* detachCapturer();
        Persister* detachPersister();
        Filter* detachLastFilter();
    
	virtual void process(int iterations) = 0;

    protected:
        vector<Filter*> filters;
        Capturer* capturer;
        Persister* persister;
};

#endif
