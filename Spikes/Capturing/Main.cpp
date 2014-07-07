#include <iostream>
#include <fstream>

#include "RTSPCapturer.h"

using namespace std;

int main()
{
	//Capturer* cap = new RTSPCapturer("/home/zane/Documents/COS301/MainProject/Resources/video41.mjpg");
	
	VideoCapture vcap;
    Mat image;

    const string videoStreamAddress = "/home/zane/Desktop/Megamind.avi";
    ifstream fin("/home/zane/Desktop/Chuck.S02E16.HDTV.XviD-XOR.avi");
    if (!fin)  // check to see if file exists
    {
		cout << "No such file" << endl;
		return 1;
	}

    //open the video stream and make sure it's opened
    if(!vcap.open(videoStreamAddress)) 
    {
        cout << "Error opening video stream or file" << std::endl;
        return -1;
    }

	while (true)
     {
        if(!vcap.read(image)) 
        {
            std::cout << "No frame" << std::endl;
            cv::waitKey();
        }
        cv::imshow("Output Window", image);
        if(cv::waitKey(1) >= 0) break;
    } 
	
	return 0;
}
