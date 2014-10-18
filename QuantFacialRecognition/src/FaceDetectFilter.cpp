#include "FaceDetectFilter.h"

FaceDetectFilter::FaceDetectFilter(string faceCascadeFilename, string faceCascadeSecondOpinionFilename)
{
    faceCascade.load(faceCascadeFilename);
    useSecondOpinion = faceCascadeSecondOpinionFilename != "";
    if (useSecondOpinion)
    {
        secondOpinion.load(faceCascadeSecondOpinionFilename);
    }
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
    faceCascade.detectMultiScale(frame, faces, 1.1, 4, 0|CV_HAAR_SCALE_IMAGE, Size(0, 0));

    for(unsigned int i = 0; i < faces.size(); i++)
    {
        Rect face_i = faces[i];
        Mat face = frame(face_i);
        vector<Rect> testFaces;
        if (useSecondOpinion)
        {
            secondOpinion.detectMultiScale(face, testFaces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(0, 0));
            if (testFaces.size() > 0)
            {
                image->addFace(face);
            }
        }
        else
        {
           image->addFace(face);
        }
    }

    return image;
}

