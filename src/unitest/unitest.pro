 
QT += testlib
QT -= gui
QT += concurrent sql

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

DEFINES += EXEMPLE_PATH=\\\"$$PWD/../../exemples/vcf/\\\"


LIBS += -L$$PWD/../bin/ -lcutevariantcore

INCLUDEPATH += $$PWD/../cutevariantcore
DEPENDPATH += $$PWD/../cutevariantcore
INCLUDEPATH += $$PWD/../cutevariantcore/datamapper
DEPENDPATH += $$PWD/../cutevariantcore/datamapper
INCLUDEPATH += $$PWD/../cutevariantcore/reader
DEPENDPATH += $$PWD/../cutevariantcore/reader
PRE_TARGETDEPS += $$PWD/../bin/libcutevariantcore.a

SOURCES += \
    tst_testcutevariant.cpp


unix {
INCLUDEPATH += "/usr/include/KF5/KArchive"
}

