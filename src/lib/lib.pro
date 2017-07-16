QT -= widgets
QT += sql

TEMPLATE = lib 

SOURCES += \
    field.cpp \
    resource.cpp \
    sample.cpp \
    region.cpp \
    genotype.cpp \
    variant.cpp \
    abstractvariantreader.cpp \
    vcfvariantreader.cpp \
    variantimporter.cpp \
    project.cpp

HEADERS += \
    field.h \
    resource.h \
    sample.h \
    region.h \
    genotype.h \
    variant.h \
    abstractvariantreader.h \
    vcfvariantreader.h \
    variantimporter.h \
    project.h

TARGET = cutevariantcore
