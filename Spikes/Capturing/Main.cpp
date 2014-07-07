#include <iostream>
#include <fstream>

#include "RTSPCapturer.h"

using namespace std;

int main()
{
	//Capturer* cap = new RTSPCapturer("/home/zane/Documents/COS301/MainProject/Resources/video41.mjpg");
	
	VideoCapture vcap;
    Mat image;

    const string videoStreamAddress = "/home/zane/mjpg_cap/video4.mjpg";
    ifstream fin("/home/zane/mjpg_cap/video4.mjpg");
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
	int cnt = 0;
	while (true)
     {
        if(!vcap.read(image)) 
        {
            std::cout << "No frame" << std::endl;
            cv::waitKey();
        }
        cv::imshow("Output Window", image);
        if(cv::waitKey(1) >= 0) break;
        cnt++;
    } 
	
	cout << cnt << endl;
	
	return 0;
}
