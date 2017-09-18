#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H
#include <QtWidgets>
#include "project.h"
#include "filterwidget.h"
#include "filteritem.h"

class FilterDialog : public QDialog
{
public:
    FilterDialog(QWidget * parent = nullptr);
    void setField(const cvar::Field& field);

    FilterItem * createFilter() const;


private:
    FilterWidget * mWidget;
    cvar::Field mField;
};

#endif // FILTERDIALOG_H
