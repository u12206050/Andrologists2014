#if !defined(_PERSISTER_H)
#define _PERSISTER_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <QTime>
#include <QDate>

#include<sstream>
#include "ImageData.h"

class Persister
{
    public:
        virtual ~Persister();
        virtual void persistImageData(ImageData* image) = 0;
};

#endif  //_PERSISTER_H
