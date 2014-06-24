#if !defined(_CONFIGREADER_H)
#define _CONFIGREADER_H

#include <string>
#include "Capturer.h"
#include "Persister.h"
#include "Filter.h"
#include <vector>

using namespace std;

class ConfigReader
{
    public:
        ConfigReader(String filename);
        Capturer* createCapturer();
        Persister* createPersister();
        vector<Filter*> createFilters();
    private:
        String filename;
};

#endif  //_CONFIGREADER_H
