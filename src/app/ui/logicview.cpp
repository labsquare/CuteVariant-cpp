#include "logicview.h"

LogicView::LogicView(QWidget * parent)
    :QTreeView(parent)
{
    mModel = new LogicModel;

    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);

    setDragDropMode(QAbstractItemView::InternalMove);
    //setDragDropMode(QAbstractItemView::DragDrop);

    setModel(mModel);

    setUniformRowHeights(true);

    setWindowTitle("Filter");

    addAction(new QAction("C"));
    addAction(new QAction("E"));
    addAction(new QAction("S"));


}

void LogicView::contextMenuEvent(QContextMenuEvent *event)
{

    QStandardItem * item = mModel->itemFromIndex(currentIndex());

    if (item)
    {
        QMenu menu;
        QAction * groupAction = menu.addAction("Create groups");
        QAction * condiAction = menu.addAction("Create Condition");
        menu.addSeparator();
        QAction * delAction = menu.addAction("Remove");


        if ( item->type() == LogicModel::ConditionType)
        {
            menu.removeAction(groupAction);
            menu.removeAction(condiAction);
        }


        QAction * choice = menu.exec(event->globalPos());

        if (choice == groupAction)
            mModel->createGroup(item);

        if (choice == condiAction)
            mModel->createCondition(item);

        if (choice == delAction)
        {
            if (item->parent())
            {
                item->parent()->removeRow(item->row());
            }

        }
    }
}

QString LogicView::query()
{
    return mModel->makeQuery();
}




