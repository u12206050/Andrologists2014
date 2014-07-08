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

    vector<Rect> faces;
    Mat grayImage;
    cvtColor(frame, grayImage, CV_BGR2GRAY);
    equalizeHist(grayImage, grayImage);
    faceCascade.detectMultiScale(frame, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30));

    for(unsigned int i = 0; i < faces.size(); i++)
    {
        Rect face_i = faces[i];
        Mat face = frame(face_i);
        image->addFace(face);
    }

    return image;
}

