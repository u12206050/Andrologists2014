#include "NSamplingFilter.h"

NSamplingFilter::NSamplingFilter(int n)
{
    counter = 0;
    this->n = n;
}

NSamplingFilter::~NSamplingFilter()
{

}

ImageData* NSamplingFilter::filter(ImageData* image)
{
    counter++;
    if(counter % n == 0)
	{
		return image;		
	}
	else
	{
        return NULL;
	}
}
