INCLUDEPATH += $$PWD

include(conditions/conditions.pri)
include(selections/selections.pri)
include(columns/columns.pri)

HEADERS += \
    $$PWD/querybuilderwidget.h

SOURCES += \
    $$PWD/querybuilderwidget.cpp

