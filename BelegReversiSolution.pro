TEMPLATE = subdirs
SUBDIRS += BelegReversi \
    BelegReversiLib \
    BelegReversiTest


BelegReversiTest.depends = BelegReversiLib
#BelegReversi.depends = BelegReversiLib
