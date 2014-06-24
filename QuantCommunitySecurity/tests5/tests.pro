include(../Defaults.pri)
TEMPLATE = app

QT       += testlib

CONFIG   += console
CONFIG   -= app_bundle
CONFIG   -= qt

SOURCES += \
    SequentialPipelineTest.cpp \
    fakes/FakeCapturer.cpp \
    fakes/FakeFilter.cpp \
    fakes/FakePersister.cpp

LIBS += -L../src -lmyapp

HEADERS += \
    SequentialPipelineTest.h \
    fakes/FakeCapturer.h \
    fakes/FakeFilter.h \
    fakes/FakePersister.h
