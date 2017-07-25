TEMPLATE = subdirs
SUBDIRS = src/lib \
            src/app

CONFIG += ordered

QMAKE_CXXFLAGS  += -Ofast


QMAKE_CXXFLAGS += -std=c++11

