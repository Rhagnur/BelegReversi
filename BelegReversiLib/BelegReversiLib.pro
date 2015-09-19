#-------------------------------------------------
#
# Project created by QtCreator 2015-09-19T18:47:30
#
#-------------------------------------------------
QT       += core gui multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

OBJECTS_DIR = tmp/obj
MOC_DIR = tmp/moc
UI_DIR = tmp/ui
RCC_DIR = tmp/qrc

TARGET = BelegReversiLib
TEMPLATE = lib

SOURCES += \
    ../BelegReversi/src/controllerField.cpp \
    ../BelegReversi/src/mainwindow.cpp \
    ../BelegReversi/src/modelField.cpp \
    ../BelegReversi/src/modelPlayer.cpp \
    ../BelegReversi/src/mydict.cpp \
    ../BelegReversi/src/sqlite.cpp \
    ../BelegReversi/src/viewField.cpp \
    ../BelegReversi/src/viewHS.cpp

HEADERS += \
    ../BelegReversi/src/controllerField.h \
    ../BelegReversi/src/mainwindow.h \
    ../BelegReversi/src/modelField.h \
    ../BelegReversi/src/modelPlayer.h \
    ../BelegReversi/src/mydict.h \
    ../BelegReversi/src/sqlite.h \
    ../BelegReversi/src/viewField.h \
    ../BelegReversi/src/viewHS.h

FORMS += ../BelegReversi/gui/mainwindow.ui \
    ../BelegReversi/gui/gamewidget.ui \
    ../BelegReversi/gui/menuwidget.ui \
    ../BelegReversi/gui/pvpwidget.ui \
    ../BelegReversi/gui/hswidget.ui \
    ../BelegReversi/gui/optionwidget.ui \
    ../BelegReversi/gui/pvcwidget.ui


RESOURCES += \
    ../BelegReversi/img/images.qrc \
    ../BelegReversi/music/music.qrc
