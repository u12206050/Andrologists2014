#if !defined(_CONFIGREADER_H)
#define _CONFIGREADER_H


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
