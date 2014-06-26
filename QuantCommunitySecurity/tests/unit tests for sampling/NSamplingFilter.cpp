#include "NSamplingFilter.h"
using namespace std;
NSamplingFilter::NSamplingFilter(int number)
{
	counter = 0;
	n = number;
}

NSamplingFilter::~NSamplingFilter()
{

}

IplImage* NSamplingFilter::filter(IplImage* image)
{
	//return every nth image
	if(counter == n)
	{
		counter = 0;
		cout << "reached counter " << n << endl;
		getchar();
		return image;		
	}
	else
	{
		counter++;
		return NULL;
	}
}