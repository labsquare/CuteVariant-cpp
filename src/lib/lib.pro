QT -= widgets
QT += sql
QT += concurrent

TEMPLATE = lib 

# KArchive

INCLUDEPATH += "/usr/include/KF5/KArchive"
LIBS +=  -L"/usr/lib"  -lKF5Archive

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
