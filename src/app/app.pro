QT += core widgets sql
QT += concurrent

DEPENDPATH += . ../lib
INCLUDEPATH += ../lib


include(queryeditor/queryeditor.pri)
include(resultsview/resultsview.pri)
include(docks/docks.pri)
include(qfonticon/qfonticon.pri)


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/release/ -lcutevariantcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/debug/ -lcutevariantcore

# My Lib
unix: LIBS += -L$$OUT_PWD/../lib/ -lcutevariantcore
INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib

# QScintilla
unix: LIBS += -L$$OUT_PWD/../qscintilla/Qt4Qt5/ -lqscintilla2
INCLUDEPATH += $$PWD/../qscintilla/Qt4Qt5/
DEPENDPATH += $$PWD/../qscintilla/Qt4Qt5/



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
