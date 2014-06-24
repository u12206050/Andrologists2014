include(../Defaults.pri)

QT += core
QT -= gui
QT += testlib

TEMPLATE = app

CONFIG   += console
CONFIG   -= app_bundle
#CONFIG   -= qt

SOURCES += \
    SequentialPipelineTest.cpp \
    main.cpp \
    FakeCapturer.cpp \
    FakeFilter.cpp \
    FakePersister.cpp

LIBS += -L../src -lapplib
LIBS += `pkg-config opencv --cflags --libs`

HEADERS += \
    SequentialPipelineTest.h \
    FakeCapturer.h \
    FakeFilter.h \
    FakePersister.h
