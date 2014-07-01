include(../Defaults.pri)

#QT += core

#QT -= gui

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
#CONFIG -= qt

SOURCES += main.cpp

LIBS += -L../src -lapplib
LIBS += `pkg-config opencv --cflags --libs`
