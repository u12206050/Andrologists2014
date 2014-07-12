#ifndef GETALLFACESINRANGERESPONSE_H
#define GETALLFACESINRANGERESPONSE_H

using namespace std;

class GetAllFacesInRangeResponse
{
	public:
		vector<QString> facesToCompareWith;
		vector<QDateTime> timestamps;
};

#endif // GETALLFACESINRANGERESPONSE_H
