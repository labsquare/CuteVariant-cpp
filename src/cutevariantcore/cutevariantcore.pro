QT -= widgets
QT += sql
QT += concurrent

TEMPLATE = lib
CONFIG += staticlib
CONFIG -= debug_and_release
CONFIG += c++14
TARGET = cutevariantcore

DESTDIR = $$PWD/../bin



INCLUDEPATH += $$PWD/../quazip/quazip
INCLUDEPATH += $$PWD/../

unix {
INCLUDEPATH += "/usr/include/KF5/KArchive"
}

 include(reader/reader.pri)
 include(datamapper/datamapper.pri)




HEADERS += \
#    bedfile.h \
#    genotype.h \
    region.h \
    sample.h \
    test.h \
    field.h \
    variant.h \
    view.h \
    cutevariant.h \
    vqlparser.h \
    importer.h \
    variantreaderfactory.h \
    querybuilder.h \
    variantquery.h

SOURCES += \
#    bedfile.cpp \
#    genotype.cpp \
    region.cpp \
    sample.cpp \
    variant.cpp \
    view.cpp \
 #   main.cpp \
    field.cpp \
    cutevariant.cpp \
    vqlparser.cpp \
    importer.cpp \
    variantreaderfactory.cpp \
    querybuilder.cpp \
    variantquery.cpp
