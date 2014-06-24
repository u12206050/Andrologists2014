#ifndef FAKECAPTURER_H
#define FAKECAPTURER_H

#include "Capturer.h"

class FakeCapturer : public Capturer
{
    public:
        FakeCapturer(ImageData* image);
        ~FakeCapturer();
        ImageData* getNextImage();
        bool getCalledFlag();

    private:
        ImageData* image;
        bool calledFlag;
};

#endif // FAKECAPTURER_H
