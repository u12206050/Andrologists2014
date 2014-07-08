#include "LocalPersisterTest.h"

void LocalPersisterTest::filterTest()
{
    QString testPath("./images/");
    Persister* persister = new LocalPersister(testPath, 0);

    ImageData* data = new ImageData;
    data->image = imread("../../testFiles/same1.jpg", CV_LOAD_IMAGE_UNCHANGED);
    data->faces.push_back(imread("../../testFiles/same2.jpg", CV_LOAD_IMAGE_UNCHANGED));
    data->faces.push_back(imread("../../testFiles/same2.jpg", CV_LOAD_IMAGE_UNCHANGED));
    data->timestamp.setMSecsSinceEpoch(10);

    persister->persistImageData(data);

    ifstream fin("./images/i_0_name_10.jpg");
    if (!fin)
    {
        QVERIFY(false);
    }

    ifstream fin1("./images/i_0_name_10_face_0.jpg");
    if (!fin1)
    {
        QVERIFY(false);
    }

    ifstream fin2("./images/i_0_name_10_face_1.jpg");
    if (!fin2)
    {
        QVERIFY(false);
    }
}
