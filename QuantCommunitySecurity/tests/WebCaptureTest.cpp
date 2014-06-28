#include "WebCaptureTest.h"
#include "WebCamCapturer.h"
#include "ImageData.h"

void WebCaptureTest::getNextImageTest()
{
    WebCamCapturer* actual;
    ImageData* data;

    try{
        actual = new WebCamCapturer();
        data = new ImageData();
    }
    catch(Exception e){
        //cout << "Here";
        return;
    }

    data = actual->getNextImage();

    QVERIFY(data != NULL);
    //QCOMPARE(data->faces.size(), 1);
    //QVERIFY(actual == NULL);
}




