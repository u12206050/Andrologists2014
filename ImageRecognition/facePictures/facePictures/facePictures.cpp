// facePictures.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/photo/photo.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/core/core_c.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv\cv.h"
#include <iostream>

using namespace cv; 
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	CvHaarClassifierCascade* face_cascade = cvLoadHaarClassifierCascade("haarcascade_frontalface_default.xml");
	CvHaarClassifierCascade* eye_cascade = cvLoadHaarClassifierCascade("haarcascade_eye.xml");
	//Mat img = loadImg("pic1.jpg");

	IplImage* img =  cvLoadImage("C:\\Users\\Gerard\\Desktop\\Gerry en Ida finaal\\IMG_0238.jpg");
	//show the original image
	cvNamedWindow("Original");
	cvShowImage("Original",img);

	//smooth the original image using Gaussian kernel to remove noise
	//cvSmooth(img, img, CV_GAUSSIAN,3,3);

	//converting the original image into grayscale
	IplImage* imgGrayScale = cvCreateImage(cvGetSize(img), 8, 1); 
	cvCvtColor(img,imgGrayScale,CV_BGR2GRAY);

	cvNamedWindow("GrayScale Image");
	cvShowImage("GrayScale Image",imgGrayScale);	
	










	/*cv faces = face_cascade.detectMultiScale(gray, 1.3, 5);
	for each (face var in faces)
	{

	} (x,y,w,h) in faces
	{
		cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2);
		roi_gray = gray[y:y+h, x:x+w];
		roi_color = img[y:y+h, x:x+w];
		eyes = eye_cascade.detectMultiScale(roi_gray);
		for (ex,ey,ew,eh) in eyes
			cv2.rectangle(roi_color,(ex,ey),(ex+ew,ey+eh),(0,255,0),2);
	}*/

	waitKey(0);
	
	//Cleanup
	cvDestroyAllWindows(); 
	//cvReleaseMemStorage(&storage);
	cvReleaseImage(&img);
	//cvReleaseImage(&imgGrayScale);
	return 0;
}

Mat loadImg(String file)
{
	Mat img = imread(file, CV_LOAD_IMAGE_UNCHANGED); //read the image data in the file "MyPic.JPG" and store it in 'img'
    if (img.empty()) //check whether the image is loaded or not    
		return Mat();
    return img;
}

void displayImg(Mat _img)
{
	namedWindow("Image_Viewer", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"
	imshow("Image_Viewer", _img); //display the image which is stored in the 'img' in the "MyWindow" window
	waitKey(0); //wait infinite time for a keypress
	destroyWindow("Image_Viewer"); //destroy the window with the name, "MyWindow"
}
