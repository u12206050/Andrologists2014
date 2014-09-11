 #include "opencv2/objdetect/objdetect.hpp"
 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"

 #include <iostream>
 #include <stdio.h>

 using namespace std;
 using namespace cv;

 /** Function Headers */
 void detectAndDisplay( Mat frame, string s );

 /** Global variables */
 String face_cascade_name = "../../testFiles/haarcascade_frontalface_alt2.xml";
 //String eyes_cascade_name = "../../testFiles/haarcascade_eye_tree_eyeglasses.xml";
 String eyes_cascade_name = "../../testFiles/haarcascade_eye.xml";
 CascadeClassifier face_cascade;
 CascadeClassifier eyes_cascade;
 string window_name = "Capture - Face detection";
 RNG rng(12345);

 /** @function main */
 int main( int argc, const char** argv )
 {
   //-- 1. Load the cascades
   if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
   if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };


	Mat india = imread("2.pgm", CV_LOAD_IMAGE_UNCHANGED);
	Mat barrack = imread("barrack.jpg", CV_LOAD_IMAGE_UNCHANGED);
	Mat many = imread("many.jpg", CV_LOAD_IMAGE_UNCHANGED); 
	
	//cvtColor( india, india, CV_BGR2GRAY );
	cvtColor( barrack, barrack, CV_BGR2GRAY );
	cvtColor( many, many, CV_BGR2GRAY );
	
 


   //-- 3. Apply the classifier to the frame
       if( !india.empty() )
       { detectAndDisplay( india,"0" ); }
       else
       { printf(" --(!) No captured frame -- Break!"); }
       
             /*if( !barrack.empty() )
       { detectAndDisplay( barrack,"1" ); }
       else
       { printf(" --(!) No captured frame -- Break!"); }
       
              if( !many.empty() )
       { detectAndDisplay( many,"2" ); }
       else
       { printf(" --(!) No captured frame -- Break!"); }*/
       
      
   waitKey(0); 
   return 0;
 }

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame,string s )
{
  std::vector<Rect> faces;
  Mat frame_gray = frame;

  //cvtColor( frame, frame_gray, CV_BGR2GRAY );
  //equalizeHist( frame_gray, frame_gray );

  //-- Detect faces
  face_cascade.detectMultiScale( frame_gray, faces, 1.05, 2, 0|CV_HAAR_SCALE_IMAGE, Size(0, 0) );
  cout << s << ": " << faces.size() << " faces in picture." << endl;

  for( size_t i = 0; i < faces.size(); i++ )
  {
    Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
    ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

    Mat faceROI = frame_gray( faces[i] );
    std::vector<Rect> eyes;

    //-- In each face, detect eyes
    
    //eyes_cascade.detectMultiScale( faceROI, eyes, 1.01, 4, 0 |CASCADE_FIND_BIGGEST_OBJECT, Size(0, 0) );
    eyes_cascade.detectMultiScale( faceROI, eyes, 1.01, 4, 0 |CV_HAAR_SCALE_IMAGE, Size(0, 0) );
    cout << s << ": " << eyes.size() << " eyes in picture." << endl;

    for( size_t j = 0; j < eyes.size(); j++ )
     {
       Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
       int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
       circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
     }
  }
  //-- Show what you got
  namedWindow( window_name + s, WINDOW_AUTOSIZE );
  imshow( window_name + s, frame );
 }
