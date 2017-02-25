#-------------------------------------------------
#
# Project created by QtCreator 2017-02-10T18:43:09
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CuteVariant
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h


RESOURCES += \
    resource.qrc

include(core/core.pri)
