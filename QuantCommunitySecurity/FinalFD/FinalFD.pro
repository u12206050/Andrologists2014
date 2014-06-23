#-------------------------------------------------
#
# Project created by QtCreator 2014-06-23T20:09:30
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = FinalFD
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    Filter.cpp \
    FaceDetectFilter.cpp

INCLUDEPATH += C:\\OpenCV-2.4.9\\install\\include
LIBS += -LC:\\OpenCV-2.4.9\\lib \
    -lopencv_core249.dll \
    -lopencv_highgui249.dll \
    -lopencv_imgproc249.dll \
    -lopencv_features2d249.dll \
    -lopencv_calib3d249.dll \
    -lopencv_objdetect249 \
    -lopencv_haartraining_engine

HEADERS += \
    FaceDetectFilter.h \
    ImageData.h \
    Filter.h
