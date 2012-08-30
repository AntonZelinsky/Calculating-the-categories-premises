#-------------------------------------------------
#
# Project created by QtCreator 2012-08-07T00:45:24
#
#-------------------------------------------------

QT     += core gui xml

CONFIG += release

TARGET = CTCP
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
	Table.cpp \
	AddDialog.cpp \
	NotEditableDelegate.cpp \
        widget.cpp

HEADERS  += mainwindow.h \
	Table.h \
	AddDialog.h \
	NotEditableDelegate.h \
        widget.h

FORMS    += mainwindow.ui
