#include "ConfigReader.h"

ConfigReader::ConfigReader(String filename)
{
	ifstream inputFile(filename.c_str());
	if (inputFile.is_open())
	{
		string line;
		string input;
		while (inputFile >> line)
		{
			input += line;
		}

		tokenise(input);
		config();
	}
	else
	{
		QString casue("Cannot open file");
		throw ErrorException(casue, 0);
	}
}

void ConfigReader::tokenise(string input)
{
	string token = "";

	for (unsigned int i = 0; i < input.length(); i++)
	{
		char c = input[i];
		if (c == '[' || c == ']' || c == ';' || c == '=')
		{
			if (token != "")
			{
				tokens.push(token);
				stringstream ss;
				ss << c;
				string charConvert;
				ss >> charConvert;
				tokens.push(charConvert);
				token = "";
			}
			else
			{
				tokens.push("[");
			}
		}
		else
		{
			token += c;
		}
	}
}

void ConfigReader::config()
{
	pipeline();
	capturer();
	consumeToken("[");
	string token = tokens.front();
	while (token == "NSamplingFilter" || token == "DiffSamplingFilter" || token =="FaceDetectFilter" || token == "preProcessingFilter")
	{
		filter();
        consumeToken("[");
        token = tokens.front();
	}
	persister();



}

void ConfigReader::pipeline()
{
	consumeToken("[");
	string token = tokens.front();
	if (token == "SequentialPipeline")
	{
		sequentialPipeline();
	}
	else
	{
		QString errorMsg = "Invalid pipeline type: ";
		errorMsg.append(token.c_str());
		throw ErrorException(errorMsg, 2);
	}
}

void ConfigReader::sequentialPipeline()
{
	consumeToken("SequentialPipeline");
	consumeToken("]");
	consumeToken("iterations");
	consumeToken("=");
	string token = tokens.front();
	tokens.pop();
	int n;
	stringstream(token) >> n;
	consumeToken(";");
	pipelineProduct = new SequentialPipeline();
}

void ConfigReader::capturer()
{
	consumeToken("[");
	string token = tokens.front();
	if (token == "StreamCapturer")
	{
		streamCapturer();
	}
	else
	{
		QString errorMsg = "Invalid capturer type: ";
		errorMsg.append(token.c_str());
		throw ErrorException(errorMsg, 3);
	}
}

void ConfigReader::streamCapturer()
{
	consumeToken("StreamCapturer");
	consumeToken("]");
	consumeToken("location");
	consumeToken("=");
	string token = tokens.front();
	tokens.pop();
	//work with token check if int
	consumeToken(";");
	QString location(token.c_str());
	//capturerProduct = new StreamCapturer(location);
}

void ConfigReader::filter()
{
	string token = tokens.front();
	if (token == "NSamplingFilter")
	{
		nSamplingFilter();
	}
	else if (token == "DiffSamplingFilter")
	{
		diffSamplingFilter();
	}
	else if (token =="FaceDetectFilter")
	{
		faceDetectFilter();
	}
	else if (token == "PreProcessingFilter")
	{
		preProcessingFilter();
	}
	else
	{
		QString errorMsg = "Invalid filter type: ";
		errorMsg.append(token.c_str());
		throw ErrorException(errorMsg, 4);
	}
}

void ConfigReader::nSamplingFilter()
{
	consumeToken("NSamplingFilter");
	consumeToken("]");
	consumeToken("n");
	consumeToken("=");
	string token = tokens.front();
	tokens.pop();
	int n;
	stringstream(token) >> n;
	consumeToken(";");
	filters.push_back(new NSamplingFilter(n));
}

void ConfigReader::diffSamplingFilter()
{
	consumeToken("DiffSamplingFilter");
	consumeToken("]");
	consumeToken("threshold");
	consumeToken("=");
	string token = tokens.front();
	tokens.pop();
	float threshold;
	stringstream(token) >> threshold;
	consumeToken(";");
	filters.push_back(new DiffSamplingFilter(threshold));
}

void ConfigReader::faceDetectFilter()
{
	consumeToken("FaceDetectFilter");
	consumeToken("]");
	consumeToken("haar1");
	consumeToken("=");
	string token = tokens.front();
	tokens.pop();
	consumeToken(";");
	consumeToken("haar2");
	consumeToken("=");
	token = tokens.front();
	tokens.pop();
	consumeToken(";");
	//filters.push_back(new FaceDetectFilter(NULL, NULL));
}

void ConfigReader::preProcessingFilter()
{
	consumeToken("PreProcessingFilter");
	consumeToken("]");
	consumeToken("eyeCasecade1");
	consumeToken("=");
	string eyeCascade1 = tokens.front();
	tokens.pop();
	consumeToken(";");
	consumeToken("eyeCasecade2");
	consumeToken("=");
	string eyeCascade2 = tokens.front();
	tokens.pop();
	consumeToken(";");
	consumeToken("targetSquareSize");
	consumeToken("=");
	string token = tokens.front();
	tokens.pop();
	int size;
	stringstream(token) >> size;
	consumeToken(";");
	//filters.push_back(new PreProcessingFilter());
}

void ConfigReader::persister()
{
	string token = tokens.front();
	if (token == "LocalPersister")
	{
		localPersister();
	}
	else
	{
		QString errorMsg = "Invalid persister type: ";
		errorMsg.append(token.c_str());
		throw ErrorException(errorMsg, 5);
	}
}

void ConfigReader::localPersister()
{
	consumeToken("LocalPersister");
	consumeToken("]");
	consumeToken("id");
	consumeToken("=");
	string token = tokens.front();
	tokens.pop();
	int id;
	stringstream(token) >> id;
	consumeToken(";");
	consumeToken("directory");
	consumeToken("=");
	QString directory = tokens.front().c_str();
	tokens.pop();
	consumeToken(";");
	persisterProduct = new LocalPersister(directory, id);
	databasePersister();
}

void ConfigReader::databasePersister()
{
	consumeToken("[");
	consumeToken("DatabasePersister");
	consumeToken("]");

	consumeToken("type");
	consumeToken("=");
	string type = tokens.front();
	tokens.pop();
	consumeToken(";");

	consumeToken("host");
	consumeToken("=");
	string host = tokens.front();
	tokens.pop();
	consumeToken(";");

	consumeToken("name");
	consumeToken("=");
	string name = tokens.front();
	tokens.pop();
	consumeToken(";");

	consumeToken("username");
	consumeToken("=");
	string username = tokens.front();
	tokens.pop();
	consumeToken(";");

	consumeToken("password");
	consumeToken("=");
	string password = tokens.front();
	tokens.pop();
	consumeToken(";");

	consumeToken("port");
	consumeToken("=");
	string portToken = tokens.front();
	tokens.pop();
	int port;
	stringstream(portToken) >> port;
	consumeToken(";");


}

void ConfigReader::consumeToken(string expected)
{
	string token = tokens.front();
	tokens.pop();
	if (token != expected)
	{
		QString cause;
		cause.append(expected.c_str());
		cause.append(" expected, but ");
		cause.append(token.c_str());
		cause.append(" found.");
		throw ErrorException(cause, 1);
	}
}

Pipeline* ConfigReader::createPipeline()
{
	return pipelineProduct;
}

Capturer* ConfigReader::createCapturer()
{
	return capturerProduct;
}

Persister* ConfigReader::createPersister()
{
	return persisterProduct;
}

vector<Filter*> ConfigReader::createFilters()
{
	return filters;
}

