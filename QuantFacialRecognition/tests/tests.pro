include(../Defaults.pri)

QT += core
QT -= gui
QT += testlib
QT += sql

TEMPLATE = app

CONFIG   += console
CONFIG   -= app_bundle

SOURCES += \ 
    main.cpp \
    FacialFeatureRecognizerTest.cpp \
    DatabaseReaderTest.cpp

LIBS += -L../src -lapplib
LIBS += `pkg-config opencv --cflags --libs`

HEADERS += \ 
    FacialFeatureRecognizerTest.h \
    DatabaseReaderTest.h

OTHER_FILES +=
