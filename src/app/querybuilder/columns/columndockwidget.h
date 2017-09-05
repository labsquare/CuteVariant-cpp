#ifndef COLUMNDOCKWIDGET_H
#define COLUMNDOCKWIDGET_H
#include "basedockwidget.h"
#include "columnview.h"

class ColumnDockWidget : public BaseDockWidget
{
public:
    ColumnDockWidget(QWidget * parent = 0);

    void load();

private:
    ColumnView * mView;
};

#endif // COLUMNDOCKWIDGET_H
