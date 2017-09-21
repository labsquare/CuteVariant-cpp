#include "selectiondockwidget.h"

SelectionDockWidget::SelectionDockWidget(QWidget *parent)
    :BaseDockWidget(parent)
{

    mView = new SelectionView;
    mSearchView = new SearchItemView(mView);
    setTitle("selection");
    setWidget(mSearchView);


    addAction(QIcon(":/rgb.png"),"compare",this, SLOT(compare()));
    addAction(FIcon(0xf014),"delete",mView, SLOT(removeSelection()));




    //    connect(remAction,SIGNAL(triggered(bool)), mView, SLOT(removeSelection()));
    connect(mView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SIGNAL(changed()));
    connect(mView, &SelectionView::doubleClicked, [this](){emit selectionDoubleClicked(mView->currentItem()->text(0));});

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
