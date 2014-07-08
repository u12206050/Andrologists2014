#include "SequentialPipeline.h"

SequentialPipeline::~SequentialPipeline()
{

}

void SequentialPipeline::process(int iterations)
{
    bool infinite = false;
    if (iterations == -1)
    {
        infinite = true;
    }
    for (int i = 0; i < iterations || infinite; i++)
    {
        bool proceed = true;
        ImageData* imageData = capturer->getNextImage();
        for (unsigned int i = 0; i < filters.size() && proceed; i++)
        {
            if (imageData == NULL)
            {
                proceed = false;
            }
            else
            {
                imageData = filters[i]->filter(imageData);
            }
        }
        if (proceed)
        {
            persister->persistImageData(imageData);
        }
    }
}
