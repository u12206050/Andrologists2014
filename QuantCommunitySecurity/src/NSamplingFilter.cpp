#include "NSamplingFilter.h"

NSamplingFilter::NSamplingFilter(int n)
{
    counter = 1;
    this->n = n;
}

NSamplingFilter::~NSamplingFilter()
{

}

ImageData* NSamplingFilter::filter(ImageData* image)
{
	//return every nth image
    if(counter % n == 0)
	{
        counter++;
		return image;		
	}
	else
	{
		counter++;
        return NULL;
	}
}
