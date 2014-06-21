#if !defined(_FILTER_H)
#define _FILTER_H


class Filter
{
public:
	~Filter();
	virtual ImageData* filter(ImageData* image) = 0;
};

#endif  //_FILTER_H
