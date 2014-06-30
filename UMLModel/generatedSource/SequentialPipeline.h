#if !defined(_SEQUENTIALPIPELINE_H)
#define _SEQUENTIALPIPELINE_H

#include "Pipeline.h"

class SequentialPipeline : public Pipeline
{
public:
	~SequentialPipeline();
	void process();
	void process();
};

#endif  //_SEQUENTIALPIPELINE_H
