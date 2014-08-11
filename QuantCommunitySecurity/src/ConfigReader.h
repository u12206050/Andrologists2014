#if !defined(_CONFIGREADER_H)
#define _CONFIGREADER_H

#include <fstream>
#include <string>
#include "Pipeline.h"
#include "Capturer.h"
#include "Persister.h"
#include "Filter.h"
#include "ErrorException.h"
#include <queue>

using namespace std;

class ConfigReader
{
    public:
        ConfigReader(String filename);
		Pipeline* createPipeline();
        Capturer* createCapturer();
        Persister* createPersister();
        vector<Filter*> createFilters();

    private:
		void tokenise(string input);
		void config();
		void pipeline();
		void sequentialPipeline();
		void capturer();
		void streamCapturer();
		void filter();
		void nSamplingFilter();
		void diffSamplingFilter();
		void faceDetectFilter();
		void preProcessingFilter();
		void persister();
		void localPersister();
		void databasePersister();
		void consumeToken(string expected);

		queue<string> tokens;
		int currentToken;
		Pipeline* pipleline;
		Capturer* capturerProduct;
		vector<Filter*> filters;
		Persister* persisterProduct;
};

#endif  //_CONFIGREADER_H
