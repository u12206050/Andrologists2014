#-------------------------------------------------
#
# Project created by QtCreator 2014-06-23T14:21:36
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = QuantCommunitySecurity
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += `pkg-config opencv --cflags --libs`

SOURCES += main.cpp \
    SequentialPipeline.cpp \
    Pipeline.cpp \
    SamplingFilter.cpp \
    RTSPCapturer.cpp \
    PreProcessingFilter.cpp \
    Persister.cpp \
    ParallelPipeline.cpp \
    NetworkPersister.cpp \
    LocalPersister.cpp \
    Filter.cpp \
    FaceDetectFilter.cpp \
    ConfigReader.cpp \
    Capturer.cpp

OTHER_FILES +=

HEADERS += \
    SequentialPipeline.h \
    Pipeline.h \
    SamplingFilter.h \
    RTSPCapturer.h \
    PreProcessingFilter.h \
    Persister.h \
    ParallelPipeline.h \
    NetworkPersister.h \
    LocalPersister.h \
    ImageData.h \
    Filter.h \
    FaceDetectFilter.h \
    ConfigReader.h \
    Capturer.h
