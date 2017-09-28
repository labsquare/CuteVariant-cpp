QT += core widgets sql
QT += concurrent


include(queryeditor/queryeditor.pri)
include(resultsview/resultsview.pri)
include(docks/docks.pri)
include(qfonticon/qfonticon.pri)



# My Lib
unix: LIBS += -L$$OUT_PWD/../lib/ -lcutevariantcore
unix:INCLUDEPATH += $$PWD/../lib
unix:DEPENDPATH += $$PWD/../lib

# QScintilla
unix: LIBS += -L$$OUT_PWD/../qscintilla/Qt4Qt5/ -lqscintilla2
unix: INCLUDEPATH += $$PWD/../qscintilla/Qt4Qt5/
unix: DEPENDPATH += $$PWD/../qscintilla/Qt4Qt5/



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




message($$OUT_PWD/../qscintilla/Qt4Qt5/)

LIBS += -L$$OUT_PWD/../qscintilla/Qt4Qt5/release -lqscintilla2
LIBS += -L$$OUT_PWD/../lib/release -lcutevariantcore

INCLUDEPATH += $$PWD/../lib
INCLUDEPATH += $$PWD/../qscintilla/Qt4Qt5
