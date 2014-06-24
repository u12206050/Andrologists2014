#if !defined(_SEQUENTIALPIPELINE_H)
#define _SEQUENTIALPIPELINE_H

#include "Pipeline.h"

class SequentialPipeline : public Pipeline
{
    public:
        ~SequentialPipeline();
        void process(int iterations);
};

#endif  //_SEQUENTIALPIPELINE_H
