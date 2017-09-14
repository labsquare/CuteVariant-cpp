QT += core widgets sql
QT += concurrent

DEPENDPATH += . ../lib
INCLUDEPATH += ../lib


include(queryeditor/queryeditor.pri)
include(resultsview/resultsview.pri)
include(docks/docks.pri)


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/release/ -lcutevariantcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/debug/ -lcutevariantcore

else:unix: LIBS += -L$$OUT_PWD/../lib/ -lcutevariantcore

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib



RESOURCES += icons/icons.qrc

HEADERS += \
    mainwindow.h \
    importdialog.h \
    basedockwidget.h \
    linkdialog.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    importdialog.cpp \
    basedockwidget.cpp \
    linkdialog.cpp


INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib
