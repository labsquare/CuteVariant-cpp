QT += testlib
QT += sql concurrent
CONFIG += c++14
INCLUDEPATH += $$PWD/../cutevariantcore
DEPENDPATH += $$PWD/../cutevariantcore

SOURCES = \ 
    testcutevariant.cpp

DEFINES += EXEMPLE_PATH=\\\"$$PWD/../../exemples/vcf/\\\"

# Cute Variant core
LIBS += -L$$OUT_PWD/../cutevariantcore/ -lcutevariantcore
#PRE_TARGETDEPS += $$OUT_PWD/../cutevariantcore/cutevariantcore.lib
PRE_TARGETDEPS += $$OUT_PWD/../cutevariantcore/libcutevariantcore.a

# Quazip
LIBS += -L$$OUT_PWD/../quazip/quazip/ -lquazip


