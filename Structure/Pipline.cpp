#include "Pipeline"

Pipeline::~Pipeline()
{
	vector<Filter>::const_iterator iterator;
	for(iterator = filters.begin(); iterator != filters.end(); iterator++)
	{
		delete (*i);
	}
}

void Pipeline::process(Mat image)
{
	vector<Filter>::const_iterator iterator;
	for(iterator = filters.begin(); iterator != filters.end(); iterator++)
	{
		image = (*i)->filter(image);
		if (image == 0)
		{
			return;
		}
	}
}

void Pipeline::addFilter(Filter* filter)
{
	if (filter != 0)
	{
		filters.push_back(filter);
	}
}
