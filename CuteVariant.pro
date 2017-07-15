TEMPLATE = subdirs
SUBDIRS = src/lib \
            src/app

CONFIG += ordered

QMAKE_CXXFLAGS += -std=c++11
