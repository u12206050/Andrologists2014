include(../Defaults.pri)

QT += core

QT += sql

LIBS += `pkg-config opencv --cflags --libs`

TARGET = applib
TEMPLATE = lib

SOURCES += \
    SequentialPipeline.cpp \
    SamplingFilter.cpp \
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
    NSamplingFilter.cpp \
    DiffSamplingFilter.cpp \
    StreamCapturer.cpp \
    ShowImageFilter.cpp \
    DatabasePersister.cpp \
    Exception.cpp

HEADERS += \
    SequentialPipeline.h \
    SamplingFilter.h \
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
    SimilarFace.h \
    NSamplingFilter.h \
    DiffSamplingFilter.h \
    StreamCapturer.h \
    ShowImageFilter.h \
    DatabasePersister.h \
    DatabasePersistRequest.h \
    Exception.h
