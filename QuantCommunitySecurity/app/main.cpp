/*#include <QCoreApplication>*/
#include <iostream>

#include "StreamCapturer.h"
#include "LocalPersister.h"
#include "DiffSamplingFilter.h"
#include "NSamplingFilter.h"
#include "SequentialPipeline.h"
#include "FaceDetectFilter.h"
#include "ShowImageFilter.h"
#include "PreProcessingFilter.h"
#include "ConfigReader.h"

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "The application must be started with one command line argument, the path to the config file." << endl;
		return 1;
	}
	try
	{
		string configFile = argv[1];
		ConfigReader reader(configFile);
        Pipeline* pipeline = reader.createPipeline();
        QString windowName("Video Stream");
        Filter* imageShower = new ShowImageFilter(windowName);
        pipeline->attachFilter(imageShower);
        pipeline->attachCapturer(reader.createCapturer());
        pipeline->attachFilters(reader.createFilters());
        vector<Filter*> filters = reader.createFilters();
        for (unsigned int i = 0;i < filters.size(); i++)
        {
            cout << filters[i] << endl;
        }
        pipeline->attachPersister(reader.createPersister());
        pipeline->process(-1);
	}
	catch (ErrorException e)
	{
		cout << e.toString().toStdString() << endl;
	}

    return 0;
}
