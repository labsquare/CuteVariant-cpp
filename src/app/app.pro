QT += core widgets sql

DEPENDPATH += . ../lib
INCLUDEPATH += ../lib


SOURCES += \
    main.cpp \
    ui/mainwindow.cpp \
    ui/queryeditor.cpp \
    ui/queryhighlighter.cpp \
    ui/logicmodel.cpp \
    ui/logicview.cpp



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/release/ -lcutevariantcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/debug/ -lcutevariantcore
else:unix: LIBS += -L$$OUT_PWD/../lib/ -lcutevariantcore

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib

HEADERS += \
    ui/mainwindow.h \
    ui/queryeditor.h \
    ui/queryhighlighter.h \
    ui/logicmodel.h \
    ui/logicview.h
