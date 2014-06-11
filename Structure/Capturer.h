#ifndef CAPTURER_H
#define CAPTURER_H

#include "String"

using namespace std;

class Capturer
{
	public:
		Capturer(String source);
		~Capturer();
		Mat getNextFrame();
	
	private:
		CvCapture* capturer;
};

#endif
