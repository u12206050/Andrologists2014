#if !defined(_FACEDETECTFILTER_H)
#define _FACEDETECTFILTER_H

#include "Filter.h"

class FaceDetectFilter : public Filter
{
public:
	~FaceDetectFilter();
	virtual ImageData* filter(ImageData* image);
	ImageData* filter(ImageData* image);
};

#endif  //_FACEDETECTFILTER_H
