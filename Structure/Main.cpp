#include "Capturer.h"

#include "Pipeline.h"
#include "Filter.h"

#include "SamplingFilter.h"
#include "FaceDetectFilter.h"
#include "NetworkFilter.h"

using namespace std;

int main()
{
	ConfigReader configReader("some config file");
	
	Capturer capturer("someSource");
	Pipeline pipeline;
	
	//Based on settings read in by ConfigReader
	pipleline.addFilter(new SamplingFilter());
	pipleline.addFilter(new FaceDetectFilter());
	pipleline.addFilter(new NetworkFilter());
	
	//maybe could have something like this
	//pipeline.addFilters(configReader.getFilters());
	
	while (true)
	{
		Mat image = capturer.getNextFrame();
		pipeline.process(image);
	}
	
	return 0;
}
