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
#include <stdio.h>

using namespace cv; 
using namespace std;

Mat loadImg(string file)
{
	Mat img = imread(file, CV_LOAD_IMAGE_UNCHANGED); //read the image data in the file "MyPic.JPG" and store it in 'img'
    if (img.empty()) //check whether the image is loaded or not    
		throw new exception("Image could not be loaded");
    return img;
}

void displayImg(Mat _img)
{
	namedWindow("Image_Viewer", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"
	imshow("Image_Viewer", _img); //display the image which is stored in the 'img' in the "MyWindow" window
	waitKey(0); //wait infinite time for a keypress
	destroyWindow("Image_Viewer"); //destroy the window with the name, "MyWindow"
}

// Function Headers
void detectAndDisplay(Mat frame);

// Global variables
// Copy this file from opencv/data/haarscascades to target folder
string face_cascade_name = "C:\\opencv\\data\\haarcascades\\haarcascade_frontalface_alt.xml";
CascadeClassifier face_cascade;
string window_name = "Capture - Face detection";
int filenumber; // Number of file to be saved
string filename;

// Function main
int main(void)
{
    // Load the cascades
    if (!face_cascade.load(face_cascade_name))
    {
        printf("--(!)Error loading\n");
        return (-1);
    };

    // Read the image file
    Mat frame = imread("images.jpg");

    for (;;)
    {
        // Apply the classifier to the frame
        if (!frame.empty())
        {
            detectAndDisplay(frame);
        }
        else
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }

        int c = waitKey(10);

        if (27 == char(c))
        {
            break;
        }
    }

    return 0;
}

// Function detectAndDisplay
void detectAndDisplay(Mat frame)
{
    std::vector<Rect> faces;
    Mat frame_gray;
    Mat crop;
    Mat res;
    Mat gray;
    string text;
    stringstream sstm;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

// Detect faces
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

// Set Region of Interest
    cv::Rect roi_b;
    cv::Rect roi_c;

    size_t ic = 0; // ic is index of current element
    int ac = 0; // ac is area of current element

    size_t ib = 0; // ib is index of biggest element
    int ab = 0; // ab is area of biggest element

    for (ic = 0; ic < faces.size(); ic++) // Iterate through all current elements (detected faces)

    {
        roi_c.x = faces[ic].x;
        roi_c.y = faces[ic].y;
        roi_c.width = (faces[ic].width);
        roi_c.height = (faces[ic].height);

        ac = roi_c.width * roi_c.height; // Get the area of current element (detected face)

        roi_b.x = faces[ib].x;
        roi_b.y = faces[ib].y;
        roi_b.width = (faces[ib].width);
        roi_b.height = (faces[ib].height);

        ab = roi_b.width * roi_b.height; // Get the area of biggest element, at beginning it is same as "current" element

        if (ac > ab)
        {
            ib = ic;
            roi_b.x = faces[ib].x;
            roi_b.y = faces[ib].y;
            roi_b.width = (faces[ib].width);
            roi_b.height = (faces[ib].height);
        }

        crop = frame(roi_b);
        resize(crop, res, Size(128, 128), 0, 0, INTER_LINEAR); // This will be needed later while saving images
        cvtColor(crop, gray, CV_BGR2GRAY); // Convert cropped image to Grayscale

        // Form a filename
        filename = "";
        stringstream ssfn;
        ssfn << filenumber << ".png";
        filename = ssfn.str();
        filenumber++;

        imwrite(filename, gray);

        Point pt1(faces[ic].x, faces[ic].y); // Display detected faces on main window - live stream from camera
        Point pt2((faces[ic].x + faces[ic].height), (faces[ic].y + faces[ic].width));
        rectangle(frame, pt1, pt2, Scalar(0, 255, 0), 2, 8, 0);
    }

// Show image
    sstm << "Crop area size: " << roi_b.width << "x" << roi_b.height << " Filename: " << filename;
    text = sstm.str();

    putText(frame, text, cvPoint(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 255), 1, CV_AA);
    imshow("original", frame);

    if (!crop.empty())
    {
        imshow("detected", crop);
    }
    else
        destroyWindow("detected");
}
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	
//	//create the cascade classifier object used for the face and eye detection
//    CascadeClassifier face_cascade;
//	CascadeClassifier eye_cascade;
//    //load the haarcascade libraries
//    face_cascade.load("haarcascade_frontalface_alt.xml");	
//	eye_cascade.load("haarcascade_eye.xml");
//
//	IplImage* img =  cvLoadImage("C:\\Users\\Gerard\\Desktop\\we like\\IMG_0430.jpg");
//	/*cvNamedWindow("Original");
//	cvShowImage("Original",img);
//	waitKey(0);*/
//
//	////converting the original image into grayscale
//	IplImage* imgGrayScale = cvCreateImage(cvGetSize(img), 8, 1); 
//	cvCvtColor(img,imgGrayScale,CV_BGR2GRAY);	
//
//	try
//	{
//		//setup image files used in the capture process
//		//Mat captureFrame = loadImg("C:\\Users\\Gerard\\Desktop\\we like\\IMG_0430.jpg");
//		//cvNamedWindow("Original");
//		//cv::imshow("Original",captureFrame);
//		////pause for 33ms
//		//	waitKey(13);
//		//Mat grayscaleFrame;
//
//		////convert captured image to gray scale and equalize
//		//cvtColor(captureFrame, grayscaleFrame, CV_BGR2GRAY);
//		//equalizeHist(grayscaleFrame, grayscaleFrame);
//
//		//create a vector array to store the face found
//		std::vector<Rect> faces;
// 
//		//find faces and store them in the vector array
//		face_cascade.detectMultiScale(imgGrayScale, faces, 1.1, 3, CV_HAAR_SCALE_IMAGE, Size(30,30));
//		//draw a rectangle for all found faces in the vector array on the original image
//		for(int i = 0; i < faces.size(); i++)
//		{
//			Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
//			Point pt2(faces[i].x, faces[i].y);
// 
//			cvRectangle(img, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);
//		}
//		//create a window to present the results
//		namedWindow("outputCapture", 1);
//		//print the output
//		cvShowImage("outputCapture", img);
//		/*cv faces = face_cascade.detectMultiScale(gray, 1.3, 5);
//		for each (face var in faces)
//		{
//
//		} (x,y,w,h) in faces
//		{
//			cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2);
//			roi_gray = gray[y:y+h, x:x+w];
//			roi_color = img[y:y+h, x:x+w];
//			eyes = eye_cascade.detectMultiScale(roi_gray);
//			for (ex,ey,ew,eh) in eyes
//				cv2.rectangle(roi_color,(ex,ey),(ex+ew,ey+eh),(0,255,0),2);
//		}*/
//
//	}
//	catch (exception ex)
//	{
//		cout << ex.what();
//	}
//
//	waitKey(0);
//	
//	//Cleanup
//	cvDestroyAllWindows(); 
//	//cvReleaseMemStorage(&storage);
//	//cvReleaseImage(&img);
//	//cvReleaseImage(&imgGrayScale);
//	return 0;
//}
