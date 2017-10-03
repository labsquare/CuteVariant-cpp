INCLUDEPATH += $$PWD

#TODO rename dock
include(filters/filters.pri)
include(selections/selections.pri)
include(columns/columns.pri)
include(beds/beds.pri)

HEADERS += \
    $$PWD/metadatadockwidget.h

SOURCES += \
    $$PWD/metadatadockwidget.cpp


