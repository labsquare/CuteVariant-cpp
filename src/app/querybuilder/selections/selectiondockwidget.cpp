#include "selectiondockwidget.h"

SelectionDockWidget::SelectionDockWidget(QWidget *parent)
    :BaseDockWidget(parent)
{

    mView = new SelectionView;
    setTitle("selection");
    setWidget(mView);

    QAction * remAction = new QAction(QIcon::fromTheme("list-remove"),"delete");
    addAction(remAction);

    connect(remAction,SIGNAL(triggered(bool)), mView, SLOT(removeSelection()));
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
