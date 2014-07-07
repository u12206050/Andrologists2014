#-------------------------------------------------
#
# Project created by QtCreator 2014-07-01T12:12:00
#
#-------------------------------------------------

QT       += core

QT       -= gui
QT += widgets
QT += testlib
QT += sql

TARGET = DatabasePersister
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    DatabasePersister.cpp \
    DatabasePersistRequest.cpp \
    PostgreDatabasePersister.cpp

INCLUDEPATH += C:\opencv-2.4.9\\install\\include
INCLUDEPATH += C:\Program Files (x86)\PostgreSQL\9.3\include

LIBS += -LC:\opencv-2.4.9\lib \
    -lopencv_core249.dll \
    -lopencv_highgui249.dll \
    -lopencv_imgproc249.dll \
    -lopencv_features2d249.dll \
    -lopencv_calib3d249.dll \
    -lopencv_contrib249.dll \
    -lopencv_flann249.dll \
-lopencv_gpu249.dll \
-lopencv_legacy249.dll \
-lopencv_ml249.dll \
-lopencv_nonfree249.dll \
-lopencv_objdetect249.dll \
-lopencv_photo249.dll \
-lopencv_stitching249.dll \
-lopencv_video249.dll \
-lopencv_videostab249.dll



HEADERS += \
    DatabasePersister.h \
    DatabasePersistRequest.h \
    PostgreDatabasePersister.h
