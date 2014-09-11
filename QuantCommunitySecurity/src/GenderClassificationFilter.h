#if !defined(_GENDERCLASSIFICATIONFILTER_H)
#define _GENDERCLASSIFICATIONFILTER_H

#include "Filter.h"

class GenderClassificationFilter : public Filter
{
    public:
        GenderClassificationFilter(string trainingFilename);
        virtual ~GenderClassificationFilter();
        virtual ImageData* filter(ImageData* image);
    
    private:
        Ptr<FaceRecognizer> classifier;
};

#endif  //_GENDERCLASSIFICATIONFILTER_H
