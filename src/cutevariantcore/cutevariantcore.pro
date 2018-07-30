QT -= widgets
QT += sql
QT += concurrent

TEMPLATE = lib 
CONFIG += staticlib
CONFIG -= debug_and_release
CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14

Debug:DESTDIR = $$PWD/../bin
Release:DESTDIR = $$PWD/../bin


INCLUDEPATH += $$PWD/../quazip/quazip
INCLUDEPATH += $$PWD/../


include(reader/reader.pri)

SOURCES += \
    field.cpp \
    resource.cpp \
    sample.cpp \
    region.cpp \
    genotype.cpp \
    variant.cpp \
    project.cpp \
    sqlitemanager.cpp \
    fieldsmodel.cpp \
    samplemodel.cpp \
    variantquery.cpp \
    selection.cpp \
    variantlink.cpp \
    bedfile.cpp \
    vqlparser.cpp \
    variantreaderfactory.cpp \


HEADERS += \
    field.h \
    resource.h \
    sample.h \
    region.h \
    genotype.h \
    variant.h \
    project.h \
    sqlitemanager.h \
    fieldsmodel.h \
    samplemodel.h \
    variantquery.h \
    selection.h \
    variantlink.h \
    bedfile.h \
    vqlparser.h \
    variantreaderfactory.h \



TARGET = cutevariantcore
