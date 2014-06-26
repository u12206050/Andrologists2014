#ifndef FAKE_H
#define FAKE_H

class Fake
{
    public:
        Fake();
        void reset();
        int getNumCalled();

    protected:
        int numCalled;
};

#endif // FAKE_H
