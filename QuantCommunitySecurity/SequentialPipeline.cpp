#include "SequentialPipeline.h"

SequentialPipeline::~SequentialPipeline()
{

}

void SequentialPipeline::process()
{
        bool proceed = true;
        ImageData* imageData = capturer->getNextImage();
        for (int i = 0; i < filters.size() && proceed; i++)
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
