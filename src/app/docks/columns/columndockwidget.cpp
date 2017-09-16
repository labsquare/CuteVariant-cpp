#include "columndockwidget.h"

ColumnDockWidget::ColumnDockWidget(QWidget * parent):
    BaseDockWidget(parent)
{
    mView  = new ColumnView();

    setTitle("Columns");
    setWidget(mView);

    // emit changed signal when model changed
     connect(qobject_cast<ColumnModel*>(mView->model()), &ColumnModel::itemChanged,[this](){emit changed();});


}
 QStringList ColumnDockWidget::selectedColumns() const
{
     return mView->selectedColumns();
 }

 void ColumnDockWidget::reset()
 {
     mView->load();

 }
