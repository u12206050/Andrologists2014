#include "Pipeline.h"

Pipeline::~Pipeline()
{
    delete capturer;
    delete persister;
    for (int i = 0; i < filters.size(); i++)
    {
        delete filters[i];
    }
}

void Pipeline::addFilter(Filter* filter)
{
    filters.push_back(filter);
}

void Pipeline::attachCapturer(Capturer* capturer)
{
    this->capturer = capturer;
}

void Pipeline::attachPersister(Persister* persister)
{
    this->persister = persister;
}

void Pipeline::addFilters(vector<Filter*> filters)
{
    for (int i = 0; i < filters.size(); i++)
    {
        this->filters.push_back(filters[i]);
    }
}

