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
    Pipeline.cpp

OTHER_FILES +=

HEADERS += \
    SequentialPipeline.h \
    Pipeline.h
