#include "GenderClassificationFilter.h"

GenderClassificationFilter::GenderClassificationFilter(string trainingFilename)
{
    classifier = createFisherFaceRecognizer();
    classifier->load(trainingFilename);
}

GenderClassificationFilter::~GenderClassificationFilter()
{
    delete classifier;
}

ImageData* GenderClassificationFilter::filter(ImageData* image)
{
    for (int i = 0; i < image->faces.size(); i++)
    {
        image->genders.push_back(classifier->predict(image->faces[i]););
    }
    return image;
}

