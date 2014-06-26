#ifndef FAKECAPTURER_H
#define FAKECAPTURER_H

#include "Capturer.h"
#include "Fake.h"

class FakeCapturer : public Capturer, public Fake
{
    public:
        FakeCapturer(ImageData* image);
        ~FakeCapturer();
        ImageData* getNextImage();

    private:
        ImageData* image;
};

#endif // FAKECAPTURER_H
