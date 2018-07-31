QT += core widgets sql charts
QT += concurrent
CONFIG -= debug_and_release
CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14



include(queryeditor/queryeditor.pri)
include(resultsview/resultsview.pri)
include(docks/docks.pri)
include(qfonticon/qfonticon.pri)
include(importwizard/importwizard.pri)
include(widgets/widgets.pri)


TARGET = cutevariant



RESOURCES += icons/icons.qrc

HEADERS += \
    mainwindow.h \
    basedockwidget.h \
    editlinkdialog.h \
    linklistdialog.h \
    operationsetdialog.h \
    searchitemview.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    basedockwidget.cpp \
    editlinkdialog.cpp \
    linklistdialog.cpp \
    operationsetdialog.cpp \
    searchitemview.cpp


INCLUDEPATH += $$PWD/../cutevariantcore
DEPENDPATH += $$PWD/../cutevariantcore

INCLUDEPATH += $$PWD/../qscintilla/Qt4Qt5
DEPENDPATH += $$PWD/../qscintilla/Qt4Qt5

INCLUDEPATH += $$PWD/../quazip/quazip
DEPENDPATH += $$PWD/../quazip/quazip


# Cute Variant core
LIBS += -L$$OUT_PWD/../cutevariantcore/ -lcutevariantcore
#PRE_TARGETDEPS += $$OUT_PWD/../cutevariantcore/cutevariantcore.lib
PRE_TARGETDEPS += $$OUT_PWD/../cutevariantcore/libcutevariantcore.a

# QScintilla
LIBS += -L$$OUT_PWD/../qscintilla/Qt4Qt5/ -lqscintilla2
#PRE_TARGETDEPS += $$OUT_PWD/../qscintilla/Qt4Qt5/qscintilla2.lib
PRE_TARGETDEPS += $$OUT_PWD/../qscintilla/Qt4Qt5/libqscintilla2.a

# Quazip
#LIBS += -L$$OUT_PWD/../quazip/quazip/ -lquazip

target.path  = /usr/bin
INSTALLS += target


# KGZIP
unix {
INCLUDEPATH += "/usr/include/KF5/KArchive"
LIBS +=  -L"/usr/lib"  -lKF5Archive
}
