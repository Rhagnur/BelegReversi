#-------------------------------------------------
#
# Project created by QtCreator 2015-09-19T18:05:51
#
#-------------------------------------------------
QT       += core gui multimedia sql testlib widgets


TARGET = tst_belegreversitest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../BelegReversiLib
DEPENDPATH += $${INCLUDEPATH}

LIBS +=     -L../BelegReversiLib -lBelegReversiLib

SOURCES +=  tst_belegreversitest.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

QMAKE_CXXFLAGS += -std=c++11
