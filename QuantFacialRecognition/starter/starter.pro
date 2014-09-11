include(../Defaults.pri)

#QT += core
QT += sql

#QT -= gui

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
#CONFIG -= qt

SOURCES += main.cpp \

LIBS += -L../src -lapplib
