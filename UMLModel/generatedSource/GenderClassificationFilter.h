#if !defined(_GENDERCLASSIFICATIONFILTER_H)
#define _GENDERCLASSIFICATIONFILTER_H

#include "Filter.h"

class GenderClassificationFilter : public Filter
{
public:
	Ptr<FaceRecognizer> classifier;
	GenderClassificationFilter(Ptr<FaceRecognizer> classifier, QString trainingFilename);
	~GenderClassificationFilter();
	ImageData* filter(ImageData* image);
	ImageData* filter(ImageData* image);
};

#endif  //_GENDERCLASSIFICATIONFILTER_H
