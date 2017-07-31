#include "logicview.h"

LogicView::LogicView(cvar::Project *prj, QWidget * parent)
    :QTreeView(parent)
{
    mPrj      = prj;
    mModel    = new LogicModel;
    mDelegate = new LogicDelegate;

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


    QAction * addGroupAction = new QAction("Add logic",this);
    QAction * addCondAction  = new QAction("Add condition",this);

    connect(addGroupAction, &QAction::triggered, [this](){addLogic();});
    connect(addCondAction, &QAction::triggered, [this](){addCondition();});

    addAction(addGroupAction);
    addAction(addCondAction);


    setWindowTitle(tr("Conditions"));


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

void LogicView::addLogic()
{

}

void LogicView::addCondition()
{



}




