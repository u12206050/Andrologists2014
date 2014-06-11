#ifndef FACEDETECTFILTER_H
#define FACEDETECTFILTER_H

#include "Filter.h"

class FaceDetectFilter : public Filter
{
	public:
		virtual Mat filter(Mat image);
		virtual ~FaceDetectFilter();
	
	protected:
	
	private:
	
};

#endif
