#if !defined(_SIMILARFACE_H)
#define _SIMILARFACE_H

#include <QDateTime>

class SimilarFace
{
    public:
        double distance;
        Mat frame;
        QDateTime timestamp;
};

#endif  //_SIMILARFACE_H