#include "selectiondockwidget.h"

SelectionDockWidget::SelectionDockWidget(QWidget *parent)
    :BaseDockWidget(parent)
{

    mView = new SelectionView;
    setTitle("selection");
    setWidget(mView);
    addAction(new QAction(QIcon::fromTheme("list-remove"),"delete"));

    connect(mView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SIGNAL(changed()));

}

QString SelectionDockWidget::tableName() const
{
    return mView->tableName();
}

void SelectionDockWidget::reset()
{
    mView->load();
}
