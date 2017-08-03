#ifndef LOGICVIEW_H
#define LOGICVIEW_H
#include <QtWidgets>
#include "filtermodel.h"
#include "project.h"
#include "filterdelegate.h"
#include "conditiondialog.h"

class FilterView : public QTreeView
{
    Q_OBJECT
public:
    FilterView(QWidget * parent = Q_NULLPTR);
    void contextMenuEvent(QContextMenuEvent* event);
    QString query();

public Q_SLOTS:
    void addLogic();
    void addCondition();
    void editCondition(const QModelIndex& index);
    void removeSelections();


protected Q_SLOTS:
    void updateActionAvaible();




private:
    FilterModel * mModel;
    FilterDelegate * mDelegate;

    QAction * mAddLogicAction;
    QAction * mAddCondAction;
    QAction * mRemAction;


};

#endif // LOGICVIEW_H
