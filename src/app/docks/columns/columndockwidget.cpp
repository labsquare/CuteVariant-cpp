#include "columndockwidget.h"

ColumnDockWidget::ColumnDockWidget(QWidget * parent):
    BaseDockWidget(parent)
{
    mView  = new ColumnView();

    setTitle("Columns");
    setWidget(mView);


    addAction(QIcon(),"Expand", mView, SLOT(expandAll()));
    addAction(QIcon(),"Collapse", mView, SLOT(collapseAll()));

    // emit changed signal when model changed
     connect(qobject_cast<ColumnModel*>(mView->model()), &ColumnModel::itemChanged,[this](){emit changed();});

     connect(mView,SIGNAL(filterItemCreated(FilterItem*)),this,SIGNAL(filterItemCreated(FilterItem*)));

}
 QStringList ColumnDockWidget::selectedColumns() const
{
     return mView->selectedColumns();
 }

 void ColumnDockWidget::reset()
 {
    mView->load();

 }
