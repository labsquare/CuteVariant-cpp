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
    project.cpp \
    sqlitemanager.cpp \
    variantquery.cpp

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
    variantquery.h

TARGET = cutevariantcore
