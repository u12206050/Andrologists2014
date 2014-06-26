#include "NSamplingFilter.h"

NSamplingFilter::NSamplingFilter(int number)
{
	counter = 0;
	n = number;
}

NSamplingFilter::~NSamplingFilter()
{

}

ImageData* NSamplingFilter::filter(ImageData* image)
{
	//return every nth image
	if(counter == n)
	{
		counter = 0;
		return image;		
	}
	else
	{
		counter++;
		return null;
	}
}