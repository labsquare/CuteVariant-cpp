QT -= widgets
QT += sql
QT += concurrent

TEMPLATE = lib 
CONFIG += staticlib
CONFIG -= debug_and_release

Debug:DESTDIR = $$PWD/../bin
Release:DESTDIR = $$PWD/../bin


INCLUDEPATH += $$PWD/../quazip/quazip


SOURCES += \
    field.cpp \
    resource.cpp \
    sample.cpp \
    region.cpp \
    genotype.cpp \
    variant.cpp \
    abstractvariantreader.cpp \
    vcfvariantreader.cpp \
    project.cpp \
    sqlitemanager.cpp \
    fieldsmodel.cpp \
    samplemodel.cpp \
    variantquery.cpp \
    selection.cpp \
    variantlink.cpp

HEADERS += \
    field.h \
    resource.h \
    sample.h \
    region.h \
    genotype.h \
    variant.h \
    abstractvariantreader.h \
    vcfvariantreader.h \
    project.h \
    sqlitemanager.h \
    fieldsmodel.h \
    samplemodel.h \
    variantquery.h \
    selection.h \
    variantlink.h

TARGET = cutevariantcore
