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
        if (c == '[' || c == ']' || c == ';' || c == '=' || c == '\"')
		{
            stringstream ss;
            ss << c;
            string charConvert;
            ss >> charConvert;
			if (token != "")
			{
				tokens.push(token);
				tokens.push(charConvert);
				token = "";
			}
			else
			{
                tokens.push(charConvert);
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
    while (token == "NSamplingFilter" || token == "DiffSamplingFilter" || token =="FaceDetectFilter" || token == "PreProcessingFilter")
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
    if (token == "\"")
    {
        consumeToken("\"");
        token = tokens.front();
        tokens.pop();
        QString location(token.c_str());
        capturerProduct = new StreamCapturer(location);
        consumeToken("\"");
    }
    else
    {
        token = tokens.front();
        tokens.pop();
        capturerProduct = new StreamCapturer(atoi(token.c_str()));
    }
	consumeToken(";");
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
    consumeToken("haarCascade1");
	consumeToken("=");
    consumeToken("\"");
    string haarCascade1 = tokens.front();
	tokens.pop();
    consumeToken("\"");
	consumeToken(";");
    if (tokens.front() == "haarCascade2")
    {
        consumeToken("haarCascade2");
        consumeToken("=");
        consumeToken("\"");
        string haarCascade2 = tokens.front();
        tokens.pop();
        consumeToken("\"");
        consumeToken(";");
        filters.push_back(new FaceDetectFilter(haarCascade1, haarCascade2));
    }
    else
    {
        filters.push_back(new FaceDetectFilter(haarCascade1));
    }
}

void ConfigReader::preProcessingFilter()
{
	consumeToken("PreProcessingFilter");
	consumeToken("]");
    consumeToken("eyeCascade1");
	consumeToken("=");
    consumeToken("\"");
	string eyeCascade1 = tokens.front();
	tokens.pop();
    consumeToken("\"");
	consumeToken(";");
    consumeToken("eyeCascade2");
	consumeToken("=");
    consumeToken("\"");
	string eyeCascade2 = tokens.front();
	tokens.pop();
    consumeToken("\"");
	consumeToken(";");
    consumeToken("targetWidth");
	consumeToken("=");
	string token = tokens.front();
	tokens.pop();
    int targetWidth;
    stringstream(token) >> targetWidth;
	consumeToken(";");
    consumeToken("targetHeight");
    consumeToken("=");
    token = tokens.front();
    tokens.pop();
    int targetHeight;
    stringstream(token) >> targetHeight;
    consumeToken(";");
    filters.push_back(new PreProcessingFilter(targetWidth, targetHeight, eyeCascade1, eyeCascade2));
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
    consumeToken("\"");
	QString directory = tokens.front().c_str();
	tokens.pop();
    consumeToken("\"");
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
    consumeToken("\"");
    QString type(tokens.front().c_str());
	tokens.pop();
    consumeToken("\"");
	consumeToken(";");

	consumeToken("host");
	consumeToken("=");
    consumeToken("\"");
    QString host(tokens.front().c_str());
	tokens.pop();
    consumeToken("\"");
	consumeToken(";");

	consumeToken("name");
	consumeToken("=");
    consumeToken("\"");
    QString name(tokens.front().c_str());
	tokens.pop();
    consumeToken("\"");
	consumeToken(";");

	consumeToken("username");
	consumeToken("=");
    consumeToken("\"");
    QString username(tokens.front().c_str());;
	tokens.pop();
    consumeToken("\"");
	consumeToken(";");

	consumeToken("password");
	consumeToken("=");
    consumeToken("\"");
    QString password(tokens.front().c_str());
	tokens.pop();
    consumeToken("\"");
	consumeToken(";");

	consumeToken("port");
	consumeToken("=");
    QString portToken(tokens.front().c_str());
	tokens.pop();
	int port;
    stringstream(portToken.toStdString()) >> port;
	consumeToken(";");

    DatabaseConnection* conn = new DatabaseConnection(type, host, name, username, password, port);

    DatabasePersister* dbPersister = new DatabasePersister(conn);
    persisterProduct->setDatabasePersister(dbPersister);
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

