#include "FaceDetectFilter.h"

FaceDetectFilter::FaceDetectFilter(CascadeClassifier& faceCascade)
{
    this->faceCascade = faceCascade;
}

FaceDetectFilter::~FaceDetectFilter()
{

}

ImageData* FaceDetectFilter::filter(ImageData* image)
{
    Mat frame = image->image;

    image->faces.clear();

    // Detect faces
    vector<Rect> faces;
    Mat grayImage;
    cvtColor(frame, grayImage, CV_BGR2GRAY);
    equalizeHist(grayImage, grayImage);
    faceCascade.detectMultiScale(frame, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30));

    for(unsigned int i = 0; i < faces.size(); i++) {
        Rect face_i = faces[i];
        Mat face = frame(face_i);
/*
        int im_width = frame.width;
        int im_height = frame.height;

        Mat face_resized;
        resize(face, face_resized, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);
*/
        //identify faces in frame green rectangle
        //rectangle(frame, face_i, CV_RGB(0, 255,0), 1);
        image->addFace(face);
    }

    return image;
}

