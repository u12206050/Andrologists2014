#ifndef FACEDETECTFILTER_H
#define FACEDETECTFILTER_H

#include "Filter.h"
#include "ImageData.h"

class FaceDetectFilter : public Filter
{
public:
    ~FaceDetectFilter();
    virtual ImageData* filter(ImageData* image);
    ImageData* filter(ImageData* image);
};

#endif // FACEDETECTFILTER_H
