#ifndef SEQUENTIAL_PIPELINE_H
#define SEQUENTIAL_PIPELINE_H

#include "Pipeline.h"

class SequentialPipeline : public Pipeline
{
    public:
        ~SequentialPipeline();
        void process(int iterations);
};

#endif  //_SEQUENTIALPIPELINE_H
