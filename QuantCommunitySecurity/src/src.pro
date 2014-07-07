include(../Defaults.pri)

QT += core

#CONFIG -= qt

LIBS += `pkg-config opencv --cflags --libs`

TARGET = applib
TEMPLATE = lib

SOURCES += \
    SequentialPipeline.cpp \
    SamplingFilter.cpp \
    RTSPCapturer.cpp \
    PreProcessingFilter.cpp \
    Pipeline.cpp \
    Persister.cpp \
    ParallelPipeline.cpp \
    NetworkPersister.cpp \
    LocalPersister.cpp \
    Filter.cpp \
    FaceDetectFilter.cpp \
    ConfigReader.cpp \
    Capturer.cpp \
    ImageData.cpp \
    FacialFeatureRecognizer.cpp \
    WebCamCapturer.cpp

HEADERS += \
    SequentialPipeline.h \
    SamplingFilter.h \
    RTSPCapturer.h \
    PreProcessingFilter.h \
    Pipeline.h \
    Persister.h \
    ParallelPipeline.h \
    NetworkPersister.h \
    LocalPersister.h \
    ImageData.h \
    Filter.h \
    FaceDetectFilter.h \
    ConfigReader.h \
    Capturer.h \
    FacialFeatureRecognizer.h \
    GetSimilarFacesRequest.h \
    GetSimilarFacesResponse.h \
    SimilarFace.h \
    WebCamCapturer.h
