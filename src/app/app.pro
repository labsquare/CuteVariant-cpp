QT += core widgets sql
QT += concurrent
CONFIG -= debug_and_release



include(queryeditor/queryeditor.pri)
include(resultsview/resultsview.pri)
include(docks/docks.pri)
include(qfonticon/qfonticon.pri)

TARGET = app



RESOURCES += icons/icons.qrc

HEADERS += \
    mainwindow.h \
    importdialog.h \
    basedockwidget.h \
    editlinkdialog.h \
    linklistdialog.h \
    operationsetdialog.h \
    searchitemview.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    importdialog.cpp \
    basedockwidget.cpp \
    editlinkdialog.cpp \
    linklistdialog.cpp \
    operationsetdialog.cpp \
    searchitemview.cpp

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib

INCLUDEPATH += $$PWD/../qscintilla/Qt4Qt5
DEPENDPATH += $$PWD/../qscintilla/Qt4Qt5

INCLUDEPATH += $$PWD/../quazip/quazip
DEPENDPATH += $$PWD/../quazip/quazip


LIBS += -L$$OUT_PWD/../lib/ -lcutevariantcore
#PRE_TARGETDEPS += $$OUT_PWD/../lib/cutevariantcore.lib
PRE_TARGETDEPS += $$OUT_PWD/../lib/libcutevariantcore.a

# Cute Variant core
LIBS += -L$$OUT_PWD/../lib/ -lcutevariantcore
#PRE_TARGETDEPS += $$OUT_PWD/../lib/cutevariantcore.lib
PRE_TARGETDEPS += $$OUT_PWD/../lib/libcutevariantcore.a

# QScintilla
LIBS += -L$$OUT_PWD/../qscintilla/Qt4Qt5/ -lqscintilla2
#PRE_TARGETDEPS += $$OUT_PWD/../qscintilla/Qt4Qt5/qscintilla2.lib
PRE_TARGETDEPS += $$OUT_PWD/../qscintilla/Qt4Qt5/libqscintilla2.a

# Quazip
LIBS += -L$$OUT_PWD/../quazip/quazip/ -lquazip


