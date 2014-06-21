#if !defined(_IMAGEDATA_H)
#define _IMAGEDATA_H


class ImageData
{
public:
	Mat image;
	vector<Mat> faces;
	QDateTime timestamp;
};

#endif  //_IMAGEDATA_H
