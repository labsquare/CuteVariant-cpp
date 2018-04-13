TEMPLATE = subdirs
QT += testlib

SUBDIRS = src/quazip \
          src/cutevariantcore \
          src/test

CONFIG += ordered

QMAKE_CXXFLAGS  += -Ofast

CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14



