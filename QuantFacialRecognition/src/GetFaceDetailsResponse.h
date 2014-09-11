#ifndef GETFACEDETAILSRESPONSE_H
#define GETFACEDETAILSRESPONSE_H

#include <vector>

using namespace std;

class GetFaceDetailsResponse
{
    public:
        vector<QString> faceFilnames;
        vector<int> ids;
};

#endif // GETFACEDETAILSRESPONSE_H
