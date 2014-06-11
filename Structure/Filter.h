#ifndef FILTER_H
#define FILTER_H

//#include <opencv stuff>

class Filter
{
	public:
		virtual ~Filter();
		virtual Mat filter(Mat image) = 0;
	
	protected:
	
	private:
	
};

#endif
