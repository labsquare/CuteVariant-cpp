 QT += core widgets

DEPENDPATH += . ../lib
INCLUDEPATH += ../lib


SOURCES += \
    main.cpp


win32
{
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/release/ -lcutevariantcore
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/debug/ -lcutevariantcore
    else:unix: LIBS += -L$$OUT_PWD/../lib/ -lcutevariantcore

    INCLUDEPATH += $$PWD/../lib
    DEPENDPATH += $$PWD/../lib
}
unix
{
    LIBS += -L../lib/ -lcutevariantcore
}
