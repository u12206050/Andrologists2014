include(../Defaults.pri)

QT += core

QT += sql

LIBS += `pkg-config opencv --cflags --libs`

TARGET = applib
TEMPLATE = lib

SOURCES += \
    FacialFeatureRecognizer.cpp \
    Exception.cpp

HEADERS += \
    FacialFeatureRecognizer.h \
    GetSimilarFacesRequest.h \
    GetSimilarFacesResponse.h \
    Exception.h
