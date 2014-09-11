QT += core

TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = \
            src \
            app \
            tests\
            starter
app.depends = src
tests.depends = src
