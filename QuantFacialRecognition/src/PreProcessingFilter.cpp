#include "PreProcessingFilter.h"

PreProcessingFilter::PreProcessingFilter(int targetWidth, int targetHeight, string eyeCascade1Filename, string eyeCascade2Filename)
{
    eyeCascade1.load(eyeCascade1Filename);
    eyeCascade2.load(eyeCascade2Filename);
    this->targetWidth = targetWidth;
    this->targetHeight = targetHeight;
}

PreProcessingFilter::~PreProcessingFilter()
{

}

ImageData* PreProcessingFilter::filter(ImageData* image)
{
    Rect searchedLeftEye, searchedRightEye;
    Point leftEye, rightEye;
    for (unsigned int i = 0; i < image->faces.size(); i++)
    {
        image->faces[i] = getPreprocessedFace(image->faces[i], targetWidth, targetHeight, eyeCascade1, eyeCascade2, true, &leftEye, &rightEye, &searchedLeftEye, &searchedRightEye);
    }
    return image;
}

void PreProcessingFilter::detectObjectsCustom(const Mat &image, CascadeClassifier &cascade, vector<Rect> &objects, int scaledWidth, int flags, Size minFeatureSize, float searchScaleFactor, int minNeighbors)
{
    Mat gray;
    if (image.channels() == 3)
    {
        cvtColor(image, gray, CV_BGR2GRAY);
    }
    else if (image.channels() == 4)
    {
        cvtColor(image, gray, CV_BGRA2GRAY);
    }
    else
    {
        gray = image;
    }

    Mat inputImg;
    float scale = image.cols / (float)scaledWidth;
    if (image.cols > scaledWidth)
    {
        int scaledHeight = cvRound(image.rows / scale);
        resize(gray, inputImg, Size(scaledWidth, scaledHeight));
    }
    else
    {
        inputImg = gray;
    }

    Mat equalizedImg;
    equalizeHist(inputImg, equalizedImg);

    cascade.detectMultiScale(equalizedImg, objects, searchScaleFactor, minNeighbors, flags, minFeatureSize);

    if (image.cols > scaledWidth)
    {
        for (int i = 0; i < (int)objects.size(); i++)
        {
            objects[i].x = cvRound(objects[i].x * scale);
            objects[i].y = cvRound(objects[i].y * scale);
            objects[i].width = cvRound(objects[i].width * scale);
            objects[i].height = cvRound(objects[i].height * scale);
        }
    }

    for (int i = 0; i < (int)objects.size(); i++ )
    {
        if (objects[i].x < 0)
            objects[i].x = 0;
        if (objects[i].y < 0)
            objects[i].y = 0;
        if (objects[i].x + objects[i].width > image.cols)
            objects[i].x = image.cols - objects[i].width;
        if (objects[i].y + objects[i].height > image.rows)
            objects[i].y = image.rows - objects[i].height;
    }
}

void PreProcessingFilter::detectLargestObject(const Mat &image, CascadeClassifier &cascade, Rect &largestObject, int scaledWidth)
{
    int flags = CASCADE_FIND_BIGGEST_OBJECT;
    Size minFeatureSize = Size(20, 20);
    float searchScaleFactor = 1.1f;
    int minNeighbors = 4;

    vector<Rect> objects;
    detectObjectsCustom(image, cascade, objects, scaledWidth, flags, minFeatureSize, searchScaleFactor, minNeighbors);
    if (objects.size() > 0)
    {
        largestObject = (Rect)objects.at(0);
    }
    else
    {
        largestObject = Rect(-1,-1,-1,-1);
    }
}

void PreProcessingFilter::detectBothEyes(const Mat &face, CascadeClassifier &eyeCascade1, CascadeClassifier &eyeCascade2, Point &leftEye, Point &rightEye, Rect *searchedLeftEye, Rect *searchedRightEye)
{
    const float EYE_SX = 0.16f;
    const float EYE_SY = 0.26f;
    const float EYE_SW = 0.30f;
    const float EYE_SH = 0.28f;

    int leftX = cvRound(face.cols * EYE_SX);
    int topY = cvRound(face.rows * EYE_SY);
    int widthX = cvRound(face.cols * EYE_SW);
    int heightY = cvRound(face.rows * EYE_SH);
    int rightX = cvRound(face.cols * (1.0-EYE_SX-EYE_SW) );

    Mat topLeftOfFace = face(Rect(leftX, topY, widthX, heightY));
    Mat topRightOfFace = face(Rect(rightX, topY, widthX, heightY));
    Rect leftEyeRect, rightEyeRect;

    if (searchedLeftEye)
        *searchedLeftEye = Rect(leftX, topY, widthX, heightY);
    if (searchedRightEye)
        *searchedRightEye = Rect(rightX, topY, widthX, heightY);

    detectLargestObject(topLeftOfFace, eyeCascade1, leftEyeRect, topLeftOfFace.cols);
    detectLargestObject(topRightOfFace, eyeCascade1, rightEyeRect, topRightOfFace.cols);

    if (leftEyeRect.width <= 0 && !eyeCascade2.empty())
    {
        detectLargestObject(topLeftOfFace, eyeCascade2, leftEyeRect, topLeftOfFace.cols);
    }

    if (rightEyeRect.width <= 0 && !eyeCascade2.empty())
    {
        detectLargestObject(topRightOfFace, eyeCascade2, rightEyeRect, topRightOfFace.cols);
    }

    if (leftEyeRect.width > 0)
    {
        leftEyeRect.x += leftX;
        leftEyeRect.y += topY;
        leftEye = Point(leftEyeRect.x + leftEyeRect.width/2, leftEyeRect.y + leftEyeRect.height/2);
    }
    else
    {
        leftEye = Point(-1, -1);
    }

    if (rightEyeRect.width > 0)
    {
        rightEyeRect.x += rightX;
        rightEyeRect.y += topY;
        rightEye = Point(rightEyeRect.x + rightEyeRect.width/2, rightEyeRect.y + rightEyeRect.height/2);
    }
    else
    {
        rightEye = Point(-1, -1);
    }
}

void PreProcessingFilter::equalizeLeftAndRightHalves(Mat &faceImg)
{
    int w = faceImg.cols;
    int h = faceImg.rows;

    Mat wholeFace;
    equalizeHist(faceImg, wholeFace);

    int midX = w/2;
    Mat leftSide = faceImg(Rect(0,0, midX,h));
    Mat rightSide = faceImg(Rect(midX,0, w-midX,h));
    equalizeHist(leftSide, leftSide);
    equalizeHist(rightSide, rightSide);

    for (int y=0; y<h; y++)
    {
        for (int x=0; x<w; x++)
        {
            int v;
            if (x < w/4)
            {
                v = leftSide.at<uchar>(y,x);
            }
            else if (x < w*2/4)
            {
                int lv = leftSide.at<uchar>(y,x);
                int wv = wholeFace.at<uchar>(y,x);
                float f = (x - w*1/4) / (float)(w*0.25f);
                v = cvRound((1.0f - f) * lv + (f) * wv);
            }
            else if (x < w*3/4)
            {
                int rv = rightSide.at<uchar>(y,x-midX);
                int wv = wholeFace.at<uchar>(y,x);
                float f = (x - w*2/4) / (float)(w*0.25f);
                v = cvRound((1.0f - f) * wv + (f) * rv);
            }
            else
            {
                v = rightSide.at<uchar>(y,x-midX);
            }
            faceImg.at<uchar>(y,x) = v;
        }
    }
}

Mat PreProcessingFilter::getPreprocessedFace(Mat &srcImg, int desiredFaceWidth, int desiredFaceHeight, CascadeClassifier &eyeCascade1, CascadeClassifier &eyeCascade2, bool doLeftAndRightSeparately, Point *storeLeftEye, Point *storeRightEye, Rect *searchedLeftEye, Rect *searchedRightEye)
{
    if (storeLeftEye)
        storeLeftEye->x = -1;
    if (storeRightEye)
        storeRightEye->x= -1;
    if (searchedLeftEye)
        searchedLeftEye->width = -1;
    if (searchedRightEye)
        searchedRightEye->width = -1;

    Mat faceImg = srcImg;
    Mat gray;
    if (faceImg.channels() == 3)
    {
        cvtColor(faceImg, gray, CV_BGR2GRAY);
    }
    else if (faceImg.channels() == 4)
    {
        cvtColor(faceImg, gray, CV_BGRA2GRAY);
    }
    else
    {
        gray = faceImg;
    }

    Point leftEye, rightEye;
    detectBothEyes(gray, eyeCascade1, eyeCascade2, leftEye, rightEye, searchedLeftEye, searchedRightEye);

    if (storeLeftEye)
        *storeLeftEye = leftEye;
    if (storeRightEye)
        *storeRightEye = rightEye;

    if (leftEye.x >= 0 && rightEye.x >= 0)
    {
        Point2f eyesCenter = Point2f( (leftEye.x + rightEye.x) * 0.5f, (leftEye.y + rightEye.y) * 0.5f );

        double dy = (rightEye.y - leftEye.y);
        double dx = (rightEye.x - leftEye.x);
        double len = sqrt(dx*dx + dy*dy);
        double angle = atan2(dy, dx) * 180.0/CV_PI; // Convert from radians to degrees.

        const double DESIRED_RIGHT_EYE_X = (1.0f - DESIRED_LEFT_EYE_X);

        double desiredLen = (DESIRED_RIGHT_EYE_X - DESIRED_LEFT_EYE_X) * desiredFaceWidth;
        double scale = desiredLen / len;

        Mat rot_mat = getRotationMatrix2D(eyesCenter, angle, scale);

        rot_mat.at<double>(0, 2) += desiredFaceWidth * 0.5f - eyesCenter.x;
        rot_mat.at<double>(1, 2) += desiredFaceHeight * DESIRED_LEFT_EYE_Y - eyesCenter.y;

        Mat warped = Mat(desiredFaceHeight, desiredFaceWidth, CV_8U, Scalar(128));
        warpAffine(gray, warped, rot_mat, warped.size());

        if (!doLeftAndRightSeparately)
        {
            equalizeHist(warped, warped);
        }
        else
        {
            equalizeLeftAndRightHalves(warped);
        }

        Mat filtered = Mat(warped.size(), CV_8U);
        bilateralFilter(warped, filtered, 0, 20.0, 2.0);

        Mat mask = Mat(warped.size(), CV_8U, Scalar(0));
        Point faceCenter = Point( desiredFaceWidth/2, cvRound(desiredFaceHeight * FACE_ELLIPSE_CY) );
        Size size = Size( cvRound(desiredFaceWidth * FACE_ELLIPSE_W), cvRound(desiredFaceHeight * FACE_ELLIPSE_H) );
        ellipse(mask, faceCenter, size, 0, 0, 360, Scalar(255), CV_FILLED);

        Mat dstImg = Mat(warped.size(), CV_8U, Scalar(128));
        filtered.copyTo(dstImg, mask);

        return dstImg;
    }
    return Mat();
}
