#if !defined(_PERSISTER_H)
#define _PERSISTER_H

#include "ImageData.h"

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <QTime>
#include <QDate>
#include <sys/types.h>  // For stat().
#include <sys/stat.h>   // For stat().

#include <sstream>
#include <iostream>
#include <stdio.h>

using namespace std;

class Persister
{
public:
    virtual ~Persister();
    virtual void persistImageData(ImageData* image) = 0;
};

#endif  //_PERSISTER_H
