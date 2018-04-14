TEMPLATE = subdirs



SUBDIRS = src/quazip \
          src/cutevariantcore \
          src/qscintilla/Qt4Qt5/qscintilla.pro \
          src/app \
          #src/test

CONFIG += ordered

QMAKE_CXXFLAGS  += -Ofast

CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14



# Installation

desktop.path = /usr/share/applications
desktop.files += cutevariant.desktop
icons.path = /usr/share/icons/hicolor/48x48/apps
icons.files += cutevariant.png

INSTALLS += desktop icons

