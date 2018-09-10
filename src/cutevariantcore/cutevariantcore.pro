QT -= widgets
QT += sql
QT += concurrent

TEMPLATE = app
CONFIG += staticlib
CONFIG -= debug_and_release
CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14

Debug:DESTDIR = $$PWD/../bin
Release:DESTDIR = $$PWD/../bin


INCLUDEPATH += $$PWD/../quazip/quazip
INCLUDEPATH += $$PWD/../

unix {
INCLUDEPATH += "/usr/include/KF5/KArchive"
}

 include(reader/reader.pri)
 include(datamapper/datamapper.pri)



TARGET = cutevariantcore

HEADERS += \
#    bedfile.h \
#    genotype.h \
    region.h \
    sample.h \
    test.h \
    field.h \
    variant.h \
    view.h \
    cutevariant.h

SOURCES += \
#    bedfile.cpp \
#    genotype.cpp \
    region.cpp \
    sample.cpp \
    variant.cpp \
    view.cpp \
    main.cpp \
    field.cpp \
    cutevariant.cpp
