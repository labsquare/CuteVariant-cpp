#include "filterview.h"

FilterView::FilterView(QWidget * parent)
    :QTreeView(parent)
{
    mModel    = new FilterModel;
    mDelegate = new FilterDelegate;


    setItemDelegate(mDelegate);
    setModel(mModel);
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setDragDropMode(QAbstractItemView::InternalMove);
    setUniformRowHeights(true);
    setAlternatingRowColors(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);

    //header()->hide();


    //    viewport()->setAutoFillBackground( false );
    //    setFrameShape(QFrame::NoFrame);
    //setDragDropMode(QAbstractItemView::DragDrop);

    setWindowTitle("Filter");

    // select first tree item
    // selectionModel()->select(mModel->index(0,0,QModelIndex()),QItemSelectionModel::Select);

    selectionModel()->select(mModel->item(0)->index(),QItemSelectionModel::Select);

}

//----------------------------------------------------------------
QString FilterView::query()
{
    return mModel->makeQuery();
}

void FilterView::addLogic()
{
    QStandardItem * parent = mModel->itemFromIndex(currentIndex());
    mModel->addLogic(new LogicItem("AND"), parent);

}

void FilterView::addCondition(FilterItem *item)
{

    QStandardItem * parent = mModel->itemFromIndex(currentIndex());
    if (parent)
        mModel->addCondition(item, parent);

}

//----------------------------------------------------------------
void FilterView::editCondition(const QModelIndex &index)
{

    //    if (mModel->itemFromIndex(index)->type() == FilterModel::ConditionalType)
    //    {
    //        FilterItem * item = dynamic_cast<FilterItem*>(mModel->itemFromIndex(index));
    //        FilterDialog dialog(this);
    //        dialog.fromItem(item);
    //        if (dialog.exec()){

    //            *item = *dialog.toItem();
    //        }
    //    }
}
//----------------------------------------------------------------
void FilterView::removeSelections()
{

    for (QModelIndex index : selectionModel()->selectedIndexes())
    {
        if (index.parent() != QModelIndex())
            mModel->removeRow(index.row(), index.parent());
    }

}
//----------------------------------------------------------------
void FilterView::updateActionAvaible()
{
    QStandardItem * parent = mModel->itemFromIndex(currentIndex());

    qDebug()<<parent->type();

    if (parent->type() == FilterModel::LogicType)
    {
        //        mAddCondAction->setEnabled(true);
        //        mAddLogicAction->setEnabled(true);
    }

    if (parent->type() == FilterModel::ConditionalType)
    {
        //        mAddCondAction->setEnabled(false);
        //        mAddLogicAction->setEnabled(false);
    }
}




