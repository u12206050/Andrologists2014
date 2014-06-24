#if !defined(_PIPELINE_H)
#define _PIPELINE_H

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
        virtual void process() = 0;
        int getNumberOfFilters();
        void attachFilter(Filter* filter);
        void attachFilters(vector<Filter*> filters);
        void attachCapturer(Capturer* capturer);
        void attachPersister(Persister* persister);
        Capturer* detachCapturer();
        Persister* detachPersister();
        Filter* detachLastFilter();

    protected:
        vector<Filter*> filters;
        Capturer* capturer;
        Persister* persister;
};

#endif  //_PIPELINE_H
