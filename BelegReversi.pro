#-------------------------------------------------
#
# Project created by QtCreator 2015-03-03T17:47:32
#
#-------------------------------------------------

QT       += core gui multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BelegReversi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    modelField.cpp \
    controllerField.cpp \
    modelPlayer.cpp \
    viewField.cpp \
    sqlite.cpp \
    viewHS.cpp \
    mydict.cpp

HEADERS  += mainwindow.h \
    modelField.h \
    controllerField.h \
    modelPlayer.h \
    viewField.h \
    sqlite.h \
    viewHS.h \
    mydict.h

FORMS    += mainwindow.ui \
    gamewidget.ui \
    menuwidget.ui \
    pvpwidget.ui \
    hswidget.ui \
    optionwidget.ui

OTHER_FILES +=

RESOURCES += \
    img/images.qrc \
    music/music.qrc

QMAKE_CXXFLAGS += -std=c++11


DISTFILES +=



