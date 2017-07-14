 QT += core widgets

DEPENDPATH += . ../lib
INCLUDEPATH += ../lib

unix {
LIBS += -L../lib/ -lcutevariantcore
}

win32 {


}


SOURCES += \
    main.cpp


