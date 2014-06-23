#if !defined(_SEQUENTIALPIPELINE_H)
#define _SEQUENTIALPIPELINE_H

#include "Pipeline.h"

class SequentialPipeline : public Pipeline
{
public:
	void process();
	~SequentialPipeline();
	void process();
};

#endif  //_SEQUENTIALPIPELINE_H
