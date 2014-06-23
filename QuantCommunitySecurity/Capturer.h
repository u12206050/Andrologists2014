#if !defined(_CAPTURER_H)
#define _CAPTURER_H


class Capturer
{
public:
	~Capturer();
	virtual ImageData* getNextImage() = 0;
};

#endif  //_CAPTURER_H
