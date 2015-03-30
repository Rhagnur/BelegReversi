#-------------------------------------------------
#
# Project created by QtCreator 2015-03-03T17:47:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BelegReversi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    modelElement.cpp \
    modelField.cpp \
    controllerField.cpp \
    modelPlayer.cpp \
    viewField.cpp

HEADERS  += mainwindow.h \
    modelElement.h \
    modelField.h \
    controllerField.h \
    modelPlayer.h \
    viewField.h

FORMS    += mainwindow.ui

OTHER_FILES +=

RESOURCES +=
