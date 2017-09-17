#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H
#include <QtWidgets>
#include "project.h"
#include "filterwidget.h"

class FilterDialog : public QDialog
{
public:
    FilterDialog(QWidget * parent = nullptr);
    void setField(const cvar::Field& field);


private:
    FilterWidget * mWidget;
    cvar::Field mField;
};

#endif // FILTERDIALOG_H
