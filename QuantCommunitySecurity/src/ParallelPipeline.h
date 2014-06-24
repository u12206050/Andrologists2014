#if !defined(_PARALLELPIPELINE_H)
#define _PARALLELPIPELINE_H

#include "Pipeline.h"

class ParallelPipeline : public Pipeline
{
public:
	void process();
	~ParallelPipeline();
};

#endif  //_PARALLELPIPELINE_H
