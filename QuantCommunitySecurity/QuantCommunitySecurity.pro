#-------------------------------------------------
#
# Project created by QtCreator 2014-06-23T14:21:36
#
#-------------------------------------------------

QT += core

TEMPLATE = subdirs
CONFIG+=ordered
SUBDIRS = \
            src \
            app \
            tests
app.depends = src
tests.depends = src


#QT += core

#QT -= gui

#TARGET = QuantCommunitySecurity
#CONFIG += console
#CONFIG -= app_bundle

#TEMPLATE = app

#include(src/QuantCommunitySecurity.pri)

#LIBS += `pkg-config opencv --cflags --libs`

#SOURCES += \
#    src/SequentialPipeline.cpp \
#    src/SamplingFilter.cpp \
#    src/RTSPCapturer.cpp \
#    src/PreProcessingFilter.cpp \
#    src/Pipeline.cpp \
#    src/Persister.cpp \
#    src/ParallelPipeline.cpp \
#    src/NetworkPersister.cpp \
#    src/main.cpp
#    src/LocalPersister.cpp \
#    src/Filter.cpp \
#    src/FaceDetectFilter.cpp \
#    src/ConfigReader.cpp \
#    src/Capturer.cpp

#OTHER_FILES += \
 #   QuantCommunitySecurity.pri

#HEADERS += \
#    src/SequentialPipeline.h \
#    src/SamplingFilter.h \
#    src/RTSPCapturer.h \
#    src/PreProcessingFilter.h \
#    src/Pipeline.h \
#    src/Persister.h \
#    src/ParallelPipeline.h \
#    src/NetworkPersister.h \
#    src/LocalPersister.h \
#    src/ImageData.h \
#    src/Filter.h \
#    src/FaceDetectFilter.h \
#    src/ConfigReader.h \
#    src/Capturer.h
