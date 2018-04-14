#include "filterview.h"

FilterView::FilterView(QWidget * parent)
    :QTreeWidget(parent)
{
    mDelegate = new FilterDelegate;

    setItemDelegate(mDelegate);

    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setDragDropMode(QAbstractItemView::InternalMove);
    setUniformRowHeights(true);
    setAlternatingRowColors(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    //setAnimated(true);

    setWindowTitle("Filter");
    header()->hide();
    setColumnCount(3);

    header()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    header()->setSectionResizeMode(1,QHeaderView::ResizeToContents);






    connect(this, &FilterView::doubleClicked, this, &FilterView::editCondition);
    connect(this,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this, SIGNAL(changed()));

    // add and top level item
    addTopLevelItem(new LogicItem());

}


//----------------------------------------------------------------
void FilterView::addLogic(LogicItem *item)
{
    QTreeWidgetItem * parent = currentItem();

    if (!parent)
        parent = topLevelItem(0);

    if (parent->type() == FilterView::ConditionType)
    {
        qDebug()<<Q_FUNC_INFO<<"cannot append logic to condition";
        return;
    }

    if (!parent)
        parent = topLevelItem(0);

    parent->addChild(item);

    emit changed();
}
//----------------------------------------------------------------
void FilterView::addCondition(ConditionItem *item)
{
    QTreeWidgetItem * parent = currentItem();

    if (!parent)
        parent = topLevelItem(0);

    parent->addChild(item);

    emit changed();
}
//----------------------------------------------------------------
void FilterView::editCondition(const QModelIndex &index)
{

    if (itemFromIndex(index)->type() == FilterView::ConditionType)
    {
        ConditionItem * item = dynamic_cast<ConditionItem*>(itemFromIndex(index));
        FilterDialog dialog(this);
        dialog.setField(item->field());
        dialog.setCurrentOperator(item->currentOperator());
        dialog.setValue(item->value());
        if (dialog.exec()){
            ConditionItem * newItem = dialog.createCondition();
            *item = *newItem;
            delete newItem;
            emit changed();
        }
    }
}
//----------------------------------------------------------------
void FilterView::removeSelections()
{
    QList<QTreeWidgetItem*> toRemove;
    for (QTreeWidgetItem * item : selectedItems()){
        // do not remove first node
        if (item != topLevelItem(0))
            toRemove.append(item);
    }

    qDeleteAll(toRemove);

    emit changed();

}

//----------------------------------------------------------------
QString FilterView::query()
{
    QString q = recursiveQuery(topLevelItem(0));
    return q;
}
//----------------------------------------------------------------
QString FilterView::recursiveQuery(QTreeWidgetItem *item)
{

    if (item->type() == FilterView::ConditionType)
        return dynamic_cast<ConditionItem*>(item)->expression();

    QStringList list;

    if (item->type() == FilterView::LogicType)
    {
        for (int i=0; i< item->childCount(); ++i)
        {
            QString rec = recursiveQuery(item->child(i));
            if (!rec.isEmpty())
                list.append("("+rec+")");
        }

        return list.join(" "+item->text(0)+" ");
    }


}
//----------------------------------------------------------------
void FilterView::updateActionAvaible()
{
    //    QStandardItem * parent = mModel->itemFromIndex(currentIndex());

    //    qDebug()<<parent->type();

    //    if (parent->type() == FilterModel::LogicType)
    //    {
    //        //        mAddCondAction->setEnabled(true);
    //        //        mAddLogicAction->setEnabled(true);
    //    }

    //    if (parent->type() == FilterModel::ConditionalType)
    //    {
    //        //        mAddCondAction->setEnabled(false);
    //        //        mAddLogicAction->setEnabled(false);
    //    }
}




