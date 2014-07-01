#include "NSamplingFilter.h"

NSamplingFilter::NSamplingFilter(int number)
{
    counter = 1;
	n = number;
}

NSamplingFilter::~NSamplingFilter()
{

}

ImageData* NSamplingFilter::filter(ImageData* image)
{
	//return every nth image
    if(counter%n == 0)
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
