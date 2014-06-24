#include "Pipeline.h"

Pipeline::~Pipeline()
{
    if (capturer != NULL)
    {
        delete detachCapturer();
    }
    if (persister != NULL)
    {
        delete detachPersister();
    }
    while (getNumberOfFilters() > 0)
    {
        Filter* temp = detachLastFilter();
        if (temp != NULL)
        {
            delete temp;
        }
    }
}

void Pipeline::attachFilter(Filter* filter)
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

void Pipeline::attachFilters(vector<Filter*> filters)
{
    for (int i = 0; i < filters.size(); i++)
    {
        attachFilter(filters[i]);
    }
}

int Pipeline::getNumberOfFilters()
{
    return filters.size();
}

Capturer* Pipeline::detachCapturer()
{
    Capturer* temp = capturer;
    capturer = NULL;
    return temp;
}

Persister* Pipeline::detachPersister()
{
    Persister* temp = persister;
    persister = NULL;
    return temp;
}

Filter* Pipeline::detachLastFilter()
{
    if (getNumberOfFilters() == 0)
    {
        return NULL;
    }
    Filter* temp = filters.back();
    filters.pop_back();
    return temp;
}
