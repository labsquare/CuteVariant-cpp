QT += core widgets sql
QT += concurrent


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



# Cute Variant core
unix|win32: LIBS += -L$$OUT_PWD/../lib/ -lcutevariantcore
INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib
win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../lib/cutevariantcore.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../lib/libcutevariantcore.a

# QScintilla
unix|win32: LIBS += -L$$OUT_PWD/../qscintilla/Qt4Qt5/ -lqscintilla2
INCLUDEPATH += $$PWD/../qscintilla/Qt4Qt5
DEPENDPATH += $$PWD/../qscintilla/Qt4Qt5
win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../qscintilla/Qt4Qt5/qscintilla2.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../qscintilla/Qt4Qt5/libqscintilla2.a

# Quazip
unix|win32: LIBS += -L$$OUT_PWD/../quazip/quazip/ -lquazip
INCLUDEPATH += $$PWD/../quazip/quazip
DEPENDPATH += $$PWD/../quazip/quazip
