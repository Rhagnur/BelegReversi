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
    modelField.cpp \
    controllerField.cpp \
    modelPlayer.cpp \
    viewField.cpp \
    menu.cpp

HEADERS  += mainwindow.h \
    modelField.h \
    controllerField.h \
    modelPlayer.h \
    viewField.h \
    menu.h

FORMS    += mainwindow.ui \
    gamewidget.ui \
    menuwidget.ui

OTHER_FILES +=

RESOURCES += \
    img/images.qrc \
    fonts/fonts.qrc

QMAKE_CXXFLAGS += -std=c++11
