include(../Defaults.pri)

QT += core
QT -= gui
QT += testlib

TEMPLATE = app

CONFIG   += console
CONFIG   -= app_bundle

SOURCES += \
    SequentialPipelineTest.cpp \
    main.cpp \
    FakeCapturer.cpp \
    FakeFilter.cpp \
    FakePersister.cpp \
    PreProcessingFilterTest.cpp \
    Fake.cpp \
    DiffSamplingFilterTest.cpp

LIBS += -L../src -lapplib
LIBS += `pkg-config opencv --cflags --libs`

HEADERS += \
    SequentialPipelineTest.h \
    FakeCapturer.h \
    FakeFilter.h \
    FakePersister.h \
    PreProcessingFilterTest.h \
    Fake.h \
    DiffSamplingFilterTest.h

OTHER_FILES += \
    haarcascade_eye.xml \
    haarcascade_eye_tree_eyeglasses.xml \
    testFace.jpg
