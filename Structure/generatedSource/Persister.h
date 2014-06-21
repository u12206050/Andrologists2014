#if !defined(_PERSISTER_H)
#define _PERSISTER_H


class Persister
{
public:
	virtual void persistImageData(ImageData* image) = 0;
	~Persister();
};

#endif  //_PERSISTER_H
