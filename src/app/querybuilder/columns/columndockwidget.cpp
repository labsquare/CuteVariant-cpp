#include "columndockwidget.h"

ColumnDockWidget::ColumnDockWidget(QWidget * parent):
    BaseDockWidget(parent)
{
    mView  = new ColumnView();

    setTitle("Columns");
    setWidget(mView);
}

void ColumnDockWidget::load()
{
    mView->load();
}
