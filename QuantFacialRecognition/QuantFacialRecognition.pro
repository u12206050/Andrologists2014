QT += core

TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = \
            src \
            app \
            tests\
            starter\
	    getImage
app.depends = src
tests.depends = src
starter.depends = app
getImage.depends = src
