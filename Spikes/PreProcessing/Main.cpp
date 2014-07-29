#include <stdio.h>
#include <iostream>
#include <vector>

#include "opencv2/opencv.hpp"
#include <cv.h>
#include <highgui.h>

#include "FaceDetectFilter.h"


using namespace cv;
using namespace std;


const double DESIRED_LEFT_EYE_X = 0.16;     // Controls how much of the face is visible after preprocessing.
const double DESIRED_LEFT_EYE_Y = 0.14;
const double FACE_ELLIPSE_CY = 0.40;
const double FACE_ELLIPSE_W = 0.50;         // Should be atleast 0.5
const double FACE_ELLIPSE_H = 0.80;         // Controls how tall the face mask is.

void detectObjectsCustom(const Mat &img, CascadeClassifier &cascade, vector<Rect> &objects, int scaledWidth, int flags, Size minFeatureSize, float searchScaleFactor, int minNeighbors)
{
    Mat gray;
    if (img.channels() == 3) {
        cvtColor(img, gray, CV_BGR2GRAY);
    }
    else if (img.channels() == 4) {
        cvtColor(img, gray, CV_BGRA2GRAY);
    }
    else {
        // Access the input image directly, since it is already grayscale.
        gray = img;
    }

    // Possibly shrink the image, to run much faster.
    Mat inputImg;
    float scale = img.cols / (float)scaledWidth;
    if (img.cols > scaledWidth) {
        // Shrink the image while keeping the same aspect ratio.
        int scaledHeight = cvRound(img.rows / scale);
        resize(gray, inputImg, Size(scaledWidth, scaledHeight));
    }
    else {
        // Access the input image directly, since it is already small.
        inputImg = gray;
    }

    // Standardize the brightness and contrast to improve dark images.
    Mat equalizedImg;
    equalizeHist(inputImg, equalizedImg);

    // Detect objects in the small grayscale image.
    cascade.detectMultiScale(equalizedImg, objects, searchScaleFactor, minNeighbors, flags, minFeatureSize);

    // Enlarge the results if the image was temporarily shrunk before detection.
    if (img.cols > scaledWidth) {
        for (int i = 0; i < (int)objects.size(); i++ ) {
            objects[i].x = cvRound(objects[i].x * scale);
            objects[i].y = cvRound(objects[i].y * scale);
            objects[i].width = cvRound(objects[i].width * scale);
            objects[i].height = cvRound(objects[i].height * scale);
        }
    }

    // Make sure the object is completely within the image, in case it was on a border.
    for (int i = 0; i < (int)objects.size(); i++ ) {
        if (objects[i].x < 0)
            objects[i].x = 0;
        if (objects[i].y < 0)
            objects[i].y = 0;
        if (objects[i].x + objects[i].width > img.cols)
            objects[i].x = img.cols - objects[i].width;
        if (objects[i].y + objects[i].height > img.rows)
            objects[i].y = img.rows - objects[i].height;
    }

    // Return with the detected face rectangles stored in "objects".
}


// Search for just a single object in the image, such as the largest face, storing the result into 'largestObject'.
// Can use Haar cascades or LBP cascades for Face Detection, or even eye, mouth, or car detection.
// Input is temporarily shrunk to 'scaledWidth' for much faster detection, since 200 is enough to find faces.
// Note: detectLargestObject() should be faster than detectManyObjects().
void detectLargestObject(const Mat &img, CascadeClassifier &cascade, Rect &largestObject, int scaledWidth)
{
    // Only search for just 1 object (the biggest in the image).
    int flags = CASCADE_FIND_BIGGEST_OBJECT;// | CASCADE_DO_ROUGH_SEARCH;
    // Smallest object size.
    Size minFeatureSize = Size(20, 20);
    // How detailed should the search be. Must be larger than 1.0.
    float searchScaleFactor = 1.1f;
    // How much the detections should be filtered out. This should depend on how bad false detections are to your system.
    // minNeighbors=2 means lots of good+bad detections, and minNeighbors=6 means only good detections are given but some are missed.
    int minNeighbors = 4;

    // Perform Object or Face Detection, looking for just 1 object (the biggest in the image).
    vector<Rect> objects;
    detectObjectsCustom(img, cascade, objects, scaledWidth, flags, minFeatureSize, searchScaleFactor, minNeighbors);
    if (objects.size() > 0) {
        // Return the only detected object.
        largestObject = (Rect)objects.at(0);
    }
    else {
        // Return an invalid rect.
        largestObject = Rect(-1,-1,-1,-1);
    }
}


/*
// Remove the outer border of the face, so it doesn't include the background & hair.
// Keeps the center of the rectangle at the same place, rather than just dividing all values by 'scale'.
Rect scaleRectFromCenter(const Rect wholeFaceRect, float scale)
{
    float faceCenterX = wholeFaceRect.x + wholeFaceRect.width * 0.5f;
    float faceCenterY = wholeFaceRect.y + wholeFaceRect.height * 0.5f;
    float newWidth = wholeFaceRect.width * scale;
    float newHeight = wholeFaceRect.height * scale;
    Rect faceRect;
    faceRect.width = cvRound(newWidth);                        // Shrink the region
    faceRect.height = cvRound(newHeight);
    faceRect.x = cvRound(faceCenterX - newWidth * 0.5f);    // Move the region so that the center is still the same spot.
    faceRect.y = cvRound(faceCenterY - newHeight * 0.5f);
    
    return faceRect;
}
*/


void detectBothEyes(const Mat &face, CascadeClassifier &eyeCascade1, CascadeClassifier &eyeCascade2, Point &leftEye, Point &rightEye, Rect *searchedLeftEye, Rect *searchedRightEye)
{

    const float EYE_SX = 0.16f;
    const float EYE_SY = 0.26f;
    const float EYE_SW = 0.30f;
    const float EYE_SH = 0.28f;

    int leftX = cvRound(face.cols * EYE_SX);
    int topY = cvRound(face.rows * EYE_SY);
    int widthX = cvRound(face.cols * EYE_SW);
    int heightY = cvRound(face.rows * EYE_SH);
    int rightX = cvRound(face.cols * (1.0-EYE_SX-EYE_SW) );  // Start of right-eye corner

    Mat topLeftOfFace = face(Rect(leftX, topY, widthX, heightY));
    Mat topRightOfFace = face(Rect(rightX, topY, widthX, heightY));
    Rect leftEyeRect, rightEyeRect;

    // Return the search windows to the caller, if desired.
    if (searchedLeftEye)
        *searchedLeftEye = Rect(leftX, topY, widthX, heightY);
    if (searchedRightEye)
        *searchedRightEye = Rect(rightX, topY, widthX, heightY);

    // Search the left region, then the right region using the 1st eye detector.
    detectLargestObject(topLeftOfFace, eyeCascade1, leftEyeRect, topLeftOfFace.cols);
    detectLargestObject(topRightOfFace, eyeCascade1, rightEyeRect, topRightOfFace.cols);

    // If the eye was not detected, try a different cascade classifier.
    if (leftEyeRect.width <= 0 && !eyeCascade2.empty()) {
        detectLargestObject(topLeftOfFace, eyeCascade2, leftEyeRect, topLeftOfFace.cols);
        //if (leftEyeRect.width > 0)
        //    cout << "2nd eye detector LEFT SUCCESS" << endl;
        //else
        //    cout << "2nd eye detector LEFT failed" << endl;
    }
    //else
    //    cout << "1st eye detector LEFT SUCCESS" << endl;

    // If the eye was not detected, try a different cascade classifier.
    if (rightEyeRect.width <= 0 && !eyeCascade2.empty()) {
        detectLargestObject(topRightOfFace, eyeCascade2, rightEyeRect, topRightOfFace.cols);
        //if (rightEyeRect.width > 0)
        //    cout << "2nd eye detector RIGHT SUCCESS" << endl;
        //else
        //    cout << "2nd eye detector RIGHT failed" << endl;
    }
    //else
    //    cout << "1st eye detector RIGHT SUCCESS" << endl;

    if (leftEyeRect.width > 0) {   // Check if the eye was detected.
        leftEyeRect.x += leftX;    // Adjust the left-eye rectangle because the face border was removed.
        leftEyeRect.y += topY;
        leftEye = Point(leftEyeRect.x + leftEyeRect.width/2, leftEyeRect.y + leftEyeRect.height/2);
    }
    else {
        leftEye = Point(-1, -1);    // Return an invalid point
    }

    if (rightEyeRect.width > 0) { // Check if the eye was detected.
        rightEyeRect.x += rightX; // Adjust the right-eye rectangle, since it starts on the right side of the image.
        rightEyeRect.y += topY;  // Adjust the right-eye rectangle because the face border was removed.
        rightEye = Point(rightEyeRect.x + rightEyeRect.width/2, rightEyeRect.y + rightEyeRect.height/2);
    }
    else {
        rightEye = Point(-1, -1);    // Return an invalid point
    }
}


void equalizeLeftAndRightHalves(Mat &faceImg)
{


    int w = faceImg.cols;
    int h = faceImg.rows;

    // 1) First, equalize the whole face.
    Mat wholeFace;
    equalizeHist(faceImg, wholeFace);

    // 2) Equalize the left half and the right half of the face separately.
    int midX = w/2;
    Mat leftSide = faceImg(Rect(0,0, midX,h));
    Mat rightSide = faceImg(Rect(midX,0, w-midX,h));
    equalizeHist(leftSide, leftSide);
    equalizeHist(rightSide, rightSide);

    // 3) Combine the left half and right half and whole face together, so that it has a smooth transition.
    for (int y=0; y<h; y++) {
        for (int x=0; x<w; x++) {
            int v;
            if (x < w/4) {          // Left 25%: just use the left face.
                v = leftSide.at<uchar>(y,x);
            }
            else if (x < w*2/4) {   // Mid-left 25%: blend the left face & whole face.
                int lv = leftSide.at<uchar>(y,x);
                int wv = wholeFace.at<uchar>(y,x);
                // Blend more of the whole face as it moves further right along the face.
                float f = (x - w*1/4) / (float)(w*0.25f);
                v = cvRound((1.0f - f) * lv + (f) * wv);
            }
            else if (x < w*3/4) {   // Mid-right 25%: blend the right face & whole face.
                int rv = rightSide.at<uchar>(y,x-midX);
                int wv = wholeFace.at<uchar>(y,x);
                // Blend more of the right-side face as it moves further right along the face.
                float f = (x - w*2/4) / (float)(w*0.25f);
                v = cvRound((1.0f - f) * wv + (f) * rv);
            }
            else {                  // Right 25%: just use the right face.
                v = rightSide.at<uchar>(y,x-midX);
            }
            faceImg.at<uchar>(y,x) = v;
        }// end x loop
    }//end y loop
}


Mat getPreprocessedFace(Mat &srcImg, int desiredFaceWidth, int desiredFaceHeight, CascadeClassifier &eyeCascade1, CascadeClassifier &eyeCascade2, bool doLeftAndRightSeparately, Point *storeLeftEye, Point *storeRightEye, Rect *searchedLeftEye, Rect *searchedRightEye)
{

    // Mark the detected face region and eye search regions as invalid, in case they aren't detected.
    if (storeLeftEye)
        storeLeftEye->x = -1;
    if (storeRightEye)
        storeRightEye->x= -1;
    if (searchedLeftEye)
        searchedLeftEye->width = -1;
    if (searchedRightEye)
        searchedRightEye->width = -1;

        //Mat faceImg = srcImg(faceRect);    // Get the detected face image.
		Mat faceImg = srcImg;
        // If the input image is not grayscale, then convert the BGR or BGRA color image to grayscale.
        Mat gray;
        if (faceImg.channels() == 3) {
            cvtColor(faceImg, gray, CV_BGR2GRAY);
        }
        else if (faceImg.channels() == 4) {
            cvtColor(faceImg, gray, CV_BGRA2GRAY);
        }
        else {
            // Access the input image directly, since it is already grayscale.
            gray = faceImg;
        }

        // Search for the 2 eyes at the full resolution, since eye detection needs max resolution possible!
        Point leftEye, rightEye;
        detectBothEyes(gray, eyeCascade1, eyeCascade2, leftEye, rightEye, searchedLeftEye, searchedRightEye);

        // Give the eye results to the caller if desired.
        if (storeLeftEye)
            *storeLeftEye = leftEye;
        if (storeRightEye)
            *storeRightEye = rightEye;

        // Check if both eyes were detected.
        if (leftEye.x >= 0 && rightEye.x >= 0) {

            // Make the face image the same size as the training images.

            // Since we found both eyes, lets rotate & scale & translate the face so that the 2 eyes
            // line up perfectly with ideal eye positions. This makes sure that eyes will be horizontal,
            // and not too far left or right of the face, etc.

            // Get the center between the 2 eyes.
            Point2f eyesCenter = Point2f( (leftEye.x + rightEye.x) * 0.5f, (leftEye.y + rightEye.y) * 0.5f );
            // Get the angle between the 2 eyes.
            double dy = (rightEye.y - leftEye.y);
            double dx = (rightEye.x - leftEye.x);
            double len = sqrt(dx*dx + dy*dy);
            double angle = atan2(dy, dx) * 180.0/CV_PI; // Convert from radians to degrees.

            // Hand measurements shown that the left eye center should ideally be at roughly (0.19, 0.14) of a scaled face image.
            const double DESIRED_RIGHT_EYE_X = (1.0f - DESIRED_LEFT_EYE_X);
            // Get the amount we need to scale the image to be the desired fixed size we want.
            double desiredLen = (DESIRED_RIGHT_EYE_X - DESIRED_LEFT_EYE_X) * desiredFaceWidth;
            double scale = desiredLen / len;
            // Get the transformation matrix for rotating and scaling the face to the desired angle & size.
            Mat rot_mat = getRotationMatrix2D(eyesCenter, angle, scale);
            // Shift the center of the eyes to be the desired center between the eyes.
            rot_mat.at<double>(0, 2) += desiredFaceWidth * 0.5f - eyesCenter.x;
            rot_mat.at<double>(1, 2) += desiredFaceHeight * DESIRED_LEFT_EYE_Y - eyesCenter.y;

            // Rotate and scale and translate the image to the desired angle & size & position!
            // Note that we use 'w' for the height instead of 'h', because the input face has 1:1 aspect ratio.
            Mat warped = Mat(desiredFaceHeight, desiredFaceWidth, CV_8U, Scalar(128)); // Clear the output image to a default grey.
            warpAffine(gray, warped, rot_mat, warped.size());
            //imshow("warped", warped);

            // Give the image a standard brightness and contrast, in case it was too dark or had low contrast.
            if (!doLeftAndRightSeparately) {
                // Do it on the whole face.
                equalizeHist(warped, warped);
            }
            else {
                // Do it seperately for the left and right sides of the face.
                equalizeLeftAndRightHalves(warped);
            }
            //imshow("equalized", warped);

            // Use the "Bilateral Filter" to reduce pixel noise by smoothing the image, but keeping the sharp edges in the face.
            Mat filtered = Mat(warped.size(), CV_8U);
            bilateralFilter(warped, filtered, 0, 20.0, 2.0);
            //imshow("filtered", filtered);

            // Filter out the corners of the face, since we mainly just care about the middle parts.
            // Draw a filled ellipse in the middle of the face-sized image.
            Mat mask = Mat(warped.size(), CV_8U, Scalar(0)); // Start with an empty mask.
            Point faceCenter = Point( desiredFaceWidth/2, cvRound(desiredFaceHeight * FACE_ELLIPSE_CY) );
            Size size = Size( cvRound(desiredFaceWidth * FACE_ELLIPSE_W), cvRound(desiredFaceHeight * FACE_ELLIPSE_H) );
            ellipse(mask, faceCenter, size, 0, 0, 360, Scalar(255), CV_FILLED);
            //imshow("mask", mask);

            // Use the mask, to remove outside pixels.
            Mat dstImg = Mat(warped.size(), CV_8U, Scalar(128)); // Clear the output image to a default gray.

            filtered.copyTo(dstImg, mask);  // Copies non-masked pixels from filtered to dstImg.
            //imshow("dstImg", dstImg);

            return dstImg;
        /*
        else {
            // Since no eyes were found, just do a generic image resize.
            resize(gray, tmpImg, Size(w,h));
        }
        */
    }
    return Mat();
}

int main(int argc, const char *argv[])
{
	String s = argv[1];
	cout << s << endl;
	Mat image = imread("../../testFiles/FaceRec/" + s + ".jpg", CV_LOAD_IMAGE_COLOR);
	imshow("Orig image", image);
	waitKey(0);
	
	Filter* faceDetect = new FaceDetectFilter();
	ImageData* data = new ImageData();
	data->image = image;
	data = faceDetect->filter(data);
	cout << data->faces.size() << endl;
	Mat face = data->faces[0];
	waitKey(0);
	imshow("Face image", face); 
	waitKey(0);
	
	Rect searchedLeftEye, searchedRightEye; // top-left and top-right regions of the face, where eyes were searched.
    Point leftEye, rightEye;    // Position of the detected eyes.
    CascadeClassifier eyeCascade1;
    eyeCascade1.load("../../testFiles/haarcascade_eye.xml");
    CascadeClassifier eyeCascade2;
    eyeCascade2.load("../../testFiles/haarcascade_eye_tree_eyeglasses.xml");
	Mat prePrc = getPreprocessedFace(face, 92, 112, eyeCascade1, eyeCascade2, true, &leftEye, &rightEye, &searchedLeftEye, &searchedRightEye);
	waitKey(0);
	imshow("PreProc image", prePrc);
	imwrite("../../testFiles/FaceRec/" + s + "_p.jpg", prePrc);
	
	waitKey(0);   
	return 0;
}
