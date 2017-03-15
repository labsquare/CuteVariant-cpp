#ifndef FIELDVIEW_H
#define FIELDVIEW_H
#include <QtWidgets>
#include <QtCore>
#include "project.h"

class FieldView : public QTreeWidget
{
public:
    FieldView(QWidget * parent = 0);
    QStringList selectedColNames() const;
    void refresh();
};

#endif // FIELDVIEW_H
