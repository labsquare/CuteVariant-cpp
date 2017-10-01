#include "columndockwidget.h"

ColumnDockWidget::ColumnDockWidget(QWidget * parent):
    BaseDockWidget(parent)
{
    mView  = new ColumnView();

    setTitle("Fields");
    setWidget(mView);


    addAction(FIcon(0xf11c),"Expand", mView, SLOT(expandAll()));
    addAction(FIcon(0xf11b),"Collapse", mView, SLOT(collapseAll()));
    addAction(FIcon(0xf140),"test", mView, SLOT(collapseAll()));

    addActionSpacer();
    addAction(FIcon(0xf118),"Collapse", mView, SLOT(collapseAll()));


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
