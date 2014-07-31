#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "cvaux.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace std;

string window_name = "Capture - Face detection";

double getSimilarity(const Mat A, const Mat B) {
// Calculate the L2 relative error between the 2 images.
double errorL2 = norm(A, B, CV_L2);
// Scale the value since L2 is summed across all pixels.
double similarity = errorL2 / (double)(A.rows * A.cols);
return similarity;
}


static Mat norm_0_255(InputArray _src) {
    Mat src = _src.getMat();

    Mat dst;
    switch(src.channels()) {
    case 1:
        cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
        break;
    case 3:
        cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
        break;
    default:
        src.copyTo(dst);
        break;
    }
    return dst;
}

static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) 
    {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) 
    {	
		stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

static bool isSameFace(Mat face1, Mat face2, Mat W, Mat mean)
{
	Mat proj = subspaceProject(W, mean, face1.reshape(1,1));
	Mat proj2 = subspaceProject(W, mean, face2.reshape(1,1));
	
	double dist = norm(proj, proj2, NORM_L2);
	
	/*double dist = 0;
    for (int i = 0; i < proj.rows; i++)
    {
		double disti = proj.at<double>(i) - proj2.at<double>(i);
		dist += disti * disti;
	}
	double confidence = 1/ sqrt(dist);*/
    cout << "dist: " << dist << ";  ";
    
    if (dist <= 3710)//fisher = 920 eigen = 3710
    {
		return true;
	}
	
	return false;
}

static bool isSameFace2(Mat face1, Mat face2, Mat W, Mat mean)
{
	Mat proj = subspaceProject(W, mean, face1.reshape(1,1));
	Mat proj2 = subspaceProject(W, mean, face2.reshape(1,1));
	
	Mat reconstruction = subspaceReconstruct(W, mean, proj);
    reconstruction = norm_0_255(reconstruction.reshape(1, face1.rows));
    
    Mat reconstruction2 = subspaceReconstruct(W, mean, proj2);
    reconstruction2 = norm_0_255(reconstruction2.reshape(1, face2.rows));
    
    //double similarity = getSimilarity(reconstruction, reconstruction2);
    double similarity = getSimilarity(face1, face2);
    cout << "sim: " << similarity << ";  ";
    if (similarity <= 0.4)
    {
		return true;
	}
	return false;
} 

int main(int argc, const char *argv[]) 
{
    if (argc < 2) 
    {
        cout << "usage: " << argv[0] << " <csv.ext> <output_folder> " << endl;
        exit(1);
    }
    string output_folder = ".";
    if (argc == 3) 
    {
        output_folder = string(argv[2]);
    }

    string fn_csv = string(argv[1]);

    vector<Mat> images;
    vector<int> labels;
    vector<Mat> generalisationImages;
    vector<int> generalisationLabels;

    try 
    {
        read_csv(fn_csv, images, labels);
    } 
    catch (cv::Exception& e) 
    {
        cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
        exit(1);
    }
    
    if(images.size() <= 1) 
    {
        string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
        CV_Error(CV_StsError, error_message);
    }

    int height = images[0].rows;
    
    cout << "Generalisation data" << endl;
    for (int i = 0; i < 20; i++)
    {
		generalisationImages.push_back(images[images.size() - 1]);
		generalisationLabels.push_back(labels[labels.size() - 1]);
		cout << generalisationLabels[i] << endl;
		images.pop_back();
		labels.pop_back();
	}
	cout << endl;

    Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
    //model->train(images, labels);
    //model->save("training.xml");
    
    model->load("training.xml");

    Mat W = model->getMat("eigenvectors");
    Mat eValues = model->getMat("eigenvalues");
    cout << "eigens: " << W.size() << endl;
    Mat mean = model->getMat("mean");

	int dpass = 0;
	int dfail = 0;
	for (int i = 0; i < generalisationImages.size()/2; i++)
	{
		for (int j = 10; j < generalisationImages.size(); j++)
		{
			if (generalisationLabels[i] == generalisationLabels[j] && isSameFace(generalisationImages[i], generalisationImages[j], W, mean))
			{
				cout << "PASS same faces HUUUUUUH" << endl;
				dpass++;
			}
			else if (generalisationLabels[i] != generalisationLabels[j] && !isSameFace(generalisationImages[i], generalisationImages[j], W, mean))
			{
				cout << "PASS diff faces" << endl;
				dpass++;
			}
			else
			{
				cout << "FAIL" << endl;
				dfail++;
			}
		}
	}
	int pass = 0;
	int fail = 0;
	for (int i = 0; i < generalisationImages.size()/2-1; i++)
	{
		for (int j = i+1; j < generalisationImages.size()/2; j++)
		{
			if (generalisationLabels[i] == generalisationLabels[j] && isSameFace(generalisationImages[i], generalisationImages[j], W, mean))
			{
				cout << "PASS same faces" << endl;
				pass++;
			}
			else if (generalisationLabels[i] != generalisationLabels[j] && !isSameFace(generalisationImages[i], generalisationImages[j], W, mean))
			{
				cout << "PASS diff faces HUHHHHH" << endl;
				pass++;
			}
			else
			{
				cout << "FAIL" << endl;
				fail++;
			}
		}
	}
	
	for (int i = 10; i < generalisationImages.size()-1; i++)
	{
		for (int j = i+1; j < generalisationImages.size(); j++)
		{
			if (generalisationLabels[i] == generalisationLabels[j] && isSameFace(generalisationImages[i], generalisationImages[j], W, mean))
			{
				cout << "PASS same faces" << endl;
				pass++;
			}
			else if (generalisationLabels[i] != generalisationLabels[j] && !isSameFace(generalisationImages[i], generalisationImages[j], W, mean))
			{
				cout << "PASS diff faces HUHHHHH" << endl;
				pass++;
			}
			else
			{
				cout << "FAIL" << endl;
				fail++;
			}
		}
	}
	
	cout << "Pass: " << dpass << " Fail: " << dfail << endl;
	cout << "Pass: " << pass << " Fail: " << fail << endl;
	
	Mat barrack = imread("../../testFiles/FaceRec/barack_normal2_p.jpg", CV_LOAD_IMAGE_UNCHANGED);
	Mat barrack2 = imread("../../testFiles/FaceRec/barack_smile_p.jpg", CV_LOAD_IMAGE_UNCHANGED);
	
	cout << "bn: " << barrack.reshape(1,1).size() << endl;
	cout << "bn2: " << barrack2.reshape(1,1).size() << endl;
	
	if(isSameFace(barrack, barrack2, W, mean))
	{
		cout << "Barack Barack Passed" << endl;
	}
	else
	{
		cout << "Barack Barack Failed" << endl;
	}
	
	/*Mat barrack = imread("newbarrack.jpg", CV_LOAD_IMAGE_UNCHANGED);
	cvtColor( barrack, barrack, CV_BGR2GRAY );
	Mat barrack2 = imread("newbarrack2.jpg", CV_LOAD_IMAGE_UNCHANGED);
	cvtColor( barrack2, barrack2, CV_BGR2GRAY );
	Mat jacob = imread("newjacob.jpg", CV_LOAD_IMAGE_UNCHANGED);
	cvtColor( jacob, jacob, CV_BGR2GRAY );
	
	if(!isSameFace(barrack, jacob, W, mean))
	{
		cout << "Barrack Jacob Passed" << endl;
	}
	else
	{
		cout << "Barrack Jacob Failed" << endl;
	}
	
	if(isSameFace(barrack2, barrack, W, mean))
	{
		cout << "Barrack Passed" << endl;
	}
	else
	{
		cout << "Barrack Failed" << endl;
	}
	
	Mat kobus1 = imread("kobus1.jpg", CV_LOAD_IMAGE_UNCHANGED);
	Mat kobus2 = imread("kobus2.jpg", CV_LOAD_IMAGE_UNCHANGED);
	imshow("k1", kobus1);
	imshow("k2", kobus2);
	
	waitKey(0);
	
	if (isSameFace(kobus1, kobus2, W, mean))
	{
		cout << "Kobus pass" << endl;
	}
	else
	{
		cout << "Kobus fail" << endl;
	}

	/*imshow("o0", generalisationImages[0]);
	Mat proj = subspaceProject(W, mean, generalisationImages[0].reshape(1,1));
    Mat reconstruction = subspaceReconstruct(W, mean, proj);
    reconstruction = norm_0_255(reconstruction.reshape(1, generalisationImages[0].rows));
    imshow("r0", reconstruction);
    
    imshow("o7", generalisationImages[7]);
	proj = subspaceProject(W, mean, generalisationImages[7].reshape(1,1));
    Mat reconstruction1 = subspaceReconstruct(W, mean, proj);
    reconstruction1 = norm_0_255(reconstruction1.reshape(1, generalisationImages[0].rows));
    imshow("r7", reconstruction1);
    
    cout << "same person 0 & 7" << endl;
    cout << isSameFace(generalisationImages[0], generalisationImages[7], W, mean) << endl;
    cout << "similarity: " << isSameFace2(generalisationImages[0], generalisationImages[7], W, mean) << endl;
    
    imshow("o5", generalisationImages[5]);
	proj = subspaceProject(W, mean, generalisationImages[5].reshape(1,1));
    Mat reconstruction4 = subspaceReconstruct(W, mean, proj);
    reconstruction4 = norm_0_255(reconstruction4.reshape(1, generalisationImages[0].rows));
    imshow("r5", reconstruction4);
    
    cout << "same person 0 & 5" << endl;
    cout << isSameFace(generalisationImages[0], generalisationImages[5], W, mean) << endl;
    cout << "similarity: " << isSameFace2(generalisationImages[0], generalisationImages[5], W, mean) << endl;
    
    imshow("o10", generalisationImages[10]);
	proj = subspaceProject(W, mean, generalisationImages[10].reshape(1,1));
    Mat reconstruction2 = subspaceReconstruct(W, mean, proj);
    reconstruction2 = norm_0_255(reconstruction2.reshape(1, generalisationImages[0].rows));
    imshow("r10", reconstruction2);
    
    cout << "not same person 0 & 10" << endl;
    cout << isSameFace(generalisationImages[0], generalisationImages[10], W, mean) << endl;
    cout << "similarity: " << isSameFace2(generalisationImages[0], generalisationImages[10], W, mean) << endl;
    
    imshow("oT0", images[0]);
	Mat proj1 = subspaceProject(W, mean, images[0].reshape(1,1));
    Mat reconstruction3 = subspaceReconstruct(W, mean, proj1);
    reconstruction3 = norm_0_255(reconstruction3.reshape(1, images[0].rows));
    imshow("rT0", reconstruction3);
    
    cout << "not same person trained face compare" << endl;
    cout << isSameFace(generalisationImages[0], images[0], W, mean) << endl;
    cout << "similarity: " << isSameFace2(generalisationImages[0], images[0], W, mean) << endl;*/
    
    if(argc == 2) 
    {
        waitKey(0);
    }
    return 0;
}
