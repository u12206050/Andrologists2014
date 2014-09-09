include(../Defaults.pri)

QT += core

QT += sql

LIBS += `pkg-config opencv --cflags --libs`

TARGET = applib
TEMPLATE = lib

SOURCES += \
    FacialFeatureRecognizer.cpp \
    ErrorException.cpp \
    DatabaseReader.cpp \
    FaceDetectFilter.cpp \
    Filter.cpp \
    ImageData.cpp \
    PreProcessingFilter.cpp \
    DatabaseConnection.cpp \
    CaseManager.cpp

HEADERS += \
    FacialFeatureRecognizer.h \
    ErrorException.h \
    DatabaseReader.h \
    GetAllFacesInRangeResponse.h \
    FaceDetectFilter.h \
    Filter.h \
    ImageData.h \
    PreProcessingFilter.h \
    GetFaceDetailsResponse.h \
    DatabaseConnection.h \
    CaseManager.h
