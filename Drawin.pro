# HAJ
# 2014-07-28T18:06:35

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Drawin
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    evolutionmachine.cpp

HEADERS  += mainwindow.h \
    evolutionmachine.h

FORMS    += mainwindow.ui

DEFINES += USE_THREAD
