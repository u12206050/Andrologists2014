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

	}
	else
	{
		QString casue("Cannot open file");
		throw ErrorException(casue, 0);
	}
}

Pipeline* ConfigReader::createPipeline()
{
	return pipleline;
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
	consumeToken("[");
	string token = tokens.front();
	if (token == "SequentialPipeline")
	{
		pipeline();
	}
	else
	{
		QString errorMsg = "Invalid type: ";
		errorMsg.append(tokens.front().c_str());
		throw ErrorException(errorMsg, 2);
	}

}

void ConfigReader::pipeline()
{

}

void ConfigReader::sequentialPipeline()
{

}

void ConfigReader::capturer()
{

}

void ConfigReader::streamCapturer()
{

}

void ConfigReader::filter()
{

}

void ConfigReader::nSamplingFilter()
{

}

void ConfigReader::diffSamplingFilter()
{

}

void ConfigReader::faceDetectFilter()
{

}

void ConfigReader::preProcessingFilter()
{

}

void ConfigReader::persister()
{

}

void ConfigReader::localPersister()
{

}

void ConfigReader::databasePersister()
{

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

