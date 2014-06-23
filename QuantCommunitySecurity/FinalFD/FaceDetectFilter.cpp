#include "FaceDetectFilter.h"

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

FaceDetectFilter::~FaceDetectFilter()
{

}

ImageData* FaceDetectFilter::filter(ImageData* image)
{

    // Detect faces
    std::vector<Rect> faces;
    face_cascade.detectMultiScale( image, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    if (!faces.empty())
    {
        try {
                imwrite("test.png", image->image);
            }
            catch (runtime_error& ex) {
                fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
                return 1;
            }
    }

}

ImageData* FaceDetectFilter::filter(ImageData* image)
{
    // Detect faces
    std::vector<Rect> faces;
    face_cascade.detectMultiScale( image, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    if (!faces.empty())
    {
        try {
                imwrite("test.png", image->image);
            }
            catch (runtime_error& ex) {
                fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
                return 1;
            }
    }
}
