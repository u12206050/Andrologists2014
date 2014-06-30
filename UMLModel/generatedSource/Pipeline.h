#if !defined(_PIPELINE_H)
#define _PIPELINE_H


class Pipeline
{
public:
	~Pipeline();
	virtual void process() = 0;
	void addFilter(Filter* filter);
	void attachCapturer(Capturer* capturer);
	void attachPersister(Persister* persister);
	void addFilters(vector<Filter*> filters);
private:
	vector<Filter*> filters;
	Capturer* capturer;
	Persister* persister;
};

#endif  //_PIPELINE_H
