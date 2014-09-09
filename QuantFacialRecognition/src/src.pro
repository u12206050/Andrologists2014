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
    CaseAuthenticator.cpp \
    FaceDetectFilter.cpp \
    Filter.cpp \
    ImageData.cpp \
    PreProcessingFilter.cpp \
    DatabasePersister.cpp

HEADERS += \
    FacialFeatureRecognizer.h \
    ErrorException.h \
    DatabaseReader.h \
    GetAllFacesInRangeResponse.h \
    CaseAuthenticator.h \
    FaceDetectFilter.h \
    Filter.h \
    ImageData.h \
    PreProcessingFilter.h \
    DatabasePersister.h \
    DatabasePersistRequest.h \
    GetFaceDetailsResponse.h
