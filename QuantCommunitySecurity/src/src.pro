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
    Capturer.cpp

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
    Capturer.h
