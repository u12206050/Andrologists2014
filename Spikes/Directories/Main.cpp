#include <iostream>
#include <sys/stat.h>

#include "opencv2/opencv.hpp"
#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;

int main()
{
	#if defined(_WIN32)
		_mkdir("test");
		cout << "win" << endl;
	#else 
		mkdir("test", 0777);
	#endif

	Mat image = imread("img.jpg", CV_LOAD_IMAGE_UNCHANGED);
	
	//imwrite("./test/test.jpg", image);
	
	return 0;
}
