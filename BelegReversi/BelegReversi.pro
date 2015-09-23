#-------------------------------------------------
#
# Project created by QtCreator 2015-03-03T17:47:32
#
#-------------------------------------------------

QT       += core gui multimedia sql testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BelegReversi
TEMPLATE = app

DESTDIR = build
OBJECTS_DIR = tmp/obj
MOC_DIR = tmp/moc
UI_DIR = tmp/ui
RCC_DIR = tmp/qrc

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/modelField.cpp \
    src/controllerField.cpp \
    src/modelPlayer.cpp \
    src/viewField.cpp \
    src/sqlite.cpp \
    src/viewHS.cpp \
    src/mydict.cpp \
    src/ai.cpp \
    src/nodeinfo.cpp

HEADERS  += src/mainwindow.h \
    src/modelField.h \
    src/controllerField.h \
    src/modelPlayer.h \
    src/viewField.h \
    src/sqlite.h \
    src/viewHS.h \
    src/mydict.h \
    src/ai.h \
    src/tree.hh \
    src/nodeinfo.h

FORMS    += gui/mainwindow.ui \
    gui/gamewidget.ui \
    gui/menuwidget.ui \
    gui/pvpwidget.ui \
    gui/hswidget.ui \
    gui/optionwidget.ui \
    gui/pvcwidget.ui

OTHER_FILES +=

RESOURCES += \
    img/images.qrc \
    music/music.qrc

QMAKE_CXXFLAGS += -std=c++11


DISTFILES +=

deldoc.commands = rm -rf $$OUT_PWD/doc

copyfiles.depends = deldoc
copyfiles.commands = $(COPY_DIR) $$PWD/src $$OUT_PWD/doc

copydoxyconf.commands = cp $$PWD/doxygen.conf $$OUT_PWD/doc
copydoxyconf.depends = copyfiles

doxygen.depends = copydoxyconf
doxygen.commands = cd $$OUT_PWD/doc/; doxygen doxygen.conf

rmfiles.depends = doxygen
rmfiles.commands = rm $$OUT_PWD/doc/*.cpp $$OUT_PWD/doc/*.h $$OUT_PWD/doc/doxygen.conf

first.depends = $(first) rmfiles

QMAKE_EXTRA_TARGETS += first copyfiles copydoxyconf deldoc doxygen rmfiles
QMAKE_CLEAN += -r doc/ tmp/

