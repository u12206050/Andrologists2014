include(../Defaults.pri)

QT += core
QT -= gui
QT += testlib

TEMPLATE = app

CONFIG   += console
CONFIG   -= app_bundle
#CONFIG   -= qt

LIBS += -L../src -lapplib
LIBS += `pkg-config opencv --cflags --libs`

SOURCES += \
    SequentialPipelineTest.cpp \
#    main.cpp \
    FakeCapturer.cpp \
    FakeFilter.cpp \
    FakePersister.cpp

HEADERS += \
    SequentialPipelineTest.h \
    FakeCapturer.h \
    FakeFilter.h \
    FakePersister.h
