include(../Defaults.pri)

QT += core

QT += sql

LIBS += `pkg-config opencv --cflags --libs`

TARGET = applib
TEMPLATE = lib

SOURCES += \
    SequentialPipeline.cpp \
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
    ErrorException.cpp

HEADERS += \
    SequentialPipeline.h \
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
    NSamplingFilter.h \
    DiffSamplingFilter.h \
    StreamCapturer.h \
    ShowImageFilter.h \
    DatabasePersister.h \
    DatabasePersistRequest.h \
    ErrorException.h
