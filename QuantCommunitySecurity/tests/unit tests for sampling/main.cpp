#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
 #include <opencv2/highgui/highgui.hpp>
#include <sstream>
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "DiffSamplingFilter.h"
#include "NSamplingFilter.h"
using namespace std;
using namespace cv;

int main()
{
  //Unit tests for DiffSampling
	IplImage* img = NULL; //change the name (image.jpg) according to your Image filename.
    DiffSamplingFilter n = DiffSamplingFilter(10);
	n.filter(img);

	double sc = n.getScore();
	cout << "Score: " << sc << endl;
	


	//Unit tests for NSampling
	NSamplingFilter ns = NSamplingFilter(5);

	for(int i=0; i<6; i++)
	{
		ns.filter(img);
	}



    return 0;
}

