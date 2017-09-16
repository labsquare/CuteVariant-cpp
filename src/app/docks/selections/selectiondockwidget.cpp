#include "selectiondockwidget.h"

SelectionDockWidget::SelectionDockWidget(QWidget *parent)
    :BaseDockWidget(parent)
{

    mView = new SelectionView;
    setTitle("selection");
    setWidget(mView);


    addAction(QIcon::fromTheme("code-class"),"compare",this, SLOT(compare()));
    addAction(QIcon::fromTheme("list-remove"),"delete",mView, SLOT(removeSelection()));




    //    connect(remAction,SIGNAL(triggered(bool)), mView, SLOT(removeSelection()));
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

void SelectionDockWidget::compare()
{
    OperationSetDialog dialog;

    if (dialog.exec())
    {

        if (!cutevariant->sqliteManager()->createSelectionFromExpression(dialog.tableName(), dialog.expression(), dialog.mode()))
            QMessageBox::warning(this,"error","Cannot run this set expression");

        else
            reset();

    }
}
