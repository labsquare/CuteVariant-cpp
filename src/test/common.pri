 
QT += concurrent sql

LIBS += -L$$PWD/../bin/ -lcutevariantcore

INCLUDEPATH += $$PWD/../cutevariantcore
DEPENDPATH += $$PWD/../cutevariantcore

INCLUDEPATH += $$PWD/../cutevariantcore/datamapper
DEPENDPATH += $$PWD/../cutevariantcore/datamapper

INCLUDEPATH += $$PWD/../cutevariantcore/reader
DEPENDPATH += $$PWD/../cutevariantcore/reader

PRE_TARGETDEPS += $$PWD/../bin/libcutevariantcore.a



INCLUDEPATH += "/usr/include/KF5/KArchive"

