#-------------------------------------------------
#
# Project created by QtCreator 2012-08-07T00:45:24
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CTCP
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
	Table.cpp \
	AddDialog.cpp \
	NotEditableDelegate.cpp

HEADERS  += mainwindow.h \
	Table.h \
	AddDialog.h \
	NotEditableDelegate.h

FORMS    += mainwindow.ui
