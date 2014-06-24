#include "ConfigReader.h"

ConfigReader::ConfigReader(String filename)
{

}

Capturer* ConfigReader::createCapturer()
{
    return NULL;
}

Persister* ConfigReader::createPersister()
{
    return NULL;
}

vector<Filter*> ConfigReader::createFilters()
{
    return vector<Filter*>();
}

