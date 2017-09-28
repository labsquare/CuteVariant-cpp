TEMPLATE = subdirs
SUBDIRS = src/quazip \
          src/lib \
          src/qscintilla/Qt4Qt5/qscintilla.pro \
          src/app

CONFIG += ordered

QMAKE_CXXFLAGS  += -Ofast


QMAKE_CXXFLAGS += -std=c++14

