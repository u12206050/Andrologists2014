#if !defined(_GETSIMILARFACESREQUEST_H)
#define _GETSIMILARFACESREQUEST_H

#include "opencv2/core/core.hpp"
#include <QDateTime>

using namespace cv;

class GetSimilarFacesRequest
{
    public:
        Mat face;
        vector<String> facesToCompareWith;
        vector<QDateTime> timestamps;
};

#endif  //_GETSIMILARFACESREQUEST_H
