#include "filterview.h"

FilterView::FilterView(QWidget * parent)
    :QTreeView(parent)
{
    mModel    = new FilterModel;
    mDelegate = new FilterDelegate;

    setItemDelegate(mDelegate);

    viewport()->setAutoFillBackground( false );
    setFrameShape(QFrame::NoFrame);
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    header()->hide();

    setDragDropMode(QAbstractItemView::InternalMove);
    //setDragDropMode(QAbstractItemView::DragDrop);

    setModel(mModel);


    setUniformRowHeights(true);

    setWindowTitle("Filter");


    mAddLogicAction = new QAction("Add logic",this);
    mAddCondAction  = new QAction("Add condition",this);
    mRemAction      = new QAction("Remove",this);


    connect(mAddLogicAction,&QAction::triggered, [this](){addLogic();});
    connect(mAddCondAction, &QAction::triggered, [this](){addCondition();});
    connect(mRemAction, &QAction::triggered, [this](){removeSelections();});


    connect(selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(updateActionAvaible()));
    connect(this,SIGNAL(doubleClicked(QModelIndex)),this, SLOT(editCondition(QModelIndex)));

    addAction(mAddLogicAction);
    addAction(mAddCondAction);
    addAction(mRemAction);

    setWindowTitle(tr("Conditions"));




}

void FilterView::contextMenuEvent(QContextMenuEvent *event)
{

    //    QStandardItem * item = mModel->itemFromIndex(currentIndex());

    //    if (item)
    //    {
    //        QMenu menu;
    //        QAction * groupAction = menu.addAction("Create groups");
    //        QAction * condiAction = menu.addAction("Create Condition");
    //        menu.addSeparator();
    //        QAction * delAction = menu.addAction("Remove");


    //        if ( item->type() == FilterModel::ConditionType)
    //        {
    //            menu.removeAction(groupAction);
    //            menu.removeAction(condiAction);
    //        }


    //        QAction * choice = menu.exec(event->globalPos());

    //        if (choice == groupAction)
    //            mModel->createGroup(item);

    //        if (choice == condiAction)
    //            mModel->createCondition(item);

    //        if (choice == delAction)
    //        {
    //            if (item->parent())
    //            {
    //                item->parent()->removeRow(item->row());
    //            }

    //        }
    //    }
}

QString FilterView::query()
{
    return mModel->makeQuery();
}

void FilterView::addLogic()
{
    QStandardItem * parent = mModel->itemFromIndex(currentIndex());
    mModel->addLogic(new LogicItem("AND"), parent);

}

void FilterView::addCondition()
{

    ConditionDialog dialog(this);

    if (dialog.exec())
    {
        QStandardItem * parent = mModel->itemFromIndex(currentIndex());
        if (parent){
            ConditionalItem * item = dialog.toItem();
            mModel->addCondition(item, parent);
        }

    }


}

void FilterView::editCondition(const QModelIndex &index)
{

    if (mModel->itemFromIndex(index)->type() == FilterModel::ConditionalType)
    {
        ConditionalItem * item = dynamic_cast<ConditionalItem*>(mModel->itemFromIndex(index));
        ConditionDialog dialog(this);
        dialog.fromItem(item);
        if (dialog.exec()){

            *item = *dialog.toItem();
        }

    }


}
void FilterView::removeSelections()
{

    for (QModelIndex index : selectionModel()->selectedIndexes())
    {
        if (index.parent() != QModelIndex())
            mModel->removeRow(index.row(), index.parent());
    }

}

void FilterView::updateActionAvaible()
{
    QStandardItem * parent = mModel->itemFromIndex(currentIndex());

    qDebug()<<parent->type();

    if (parent->type() == FilterModel::LogicType)
    {
        mAddCondAction->setEnabled(true);
        mAddLogicAction->setEnabled(true);
    }

    if (parent->type() == FilterModel::ConditionalType)
    {
        mAddCondAction->setEnabled(false);
        mAddLogicAction->setEnabled(false);
    }
}




