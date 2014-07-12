include(../Defaults.pri)

QT += core

QT += sql

LIBS += `pkg-config opencv --cflags --libs`

TARGET = applib
TEMPLATE = lib

SOURCES += \
    FacialFeatureRecognizer.cpp \
    ErrorException.cpp \
    DatabaseReader.cpp

HEADERS += \
    FacialFeatureRecognizer.h \
    GetSimilarFacesRequest.h \
    GetSimilarFacesResponse.h \
    SimilarFace.h \
    ErrorException.h \
    DatabaseReader.h \
    GetAllFacesInRangeResponse.h
