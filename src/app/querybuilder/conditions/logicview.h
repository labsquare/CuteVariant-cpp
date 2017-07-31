#ifndef LOGICVIEW_H
#define LOGICVIEW_H
#include <QtWidgets>
#include "logicmodel.h"
#include "project.h"
#include "logicdelegate.h"
#include "conditiondialog.h"

class LogicView : public QTreeView
{
    Q_OBJECT
public:
    LogicView(QWidget * parent = Q_NULLPTR);
    void contextMenuEvent(QContextMenuEvent* event);
    QString query();

public Q_SLOTS:
    void addLogic();
    void addCondition();



private:
    LogicModel * mModel;
    LogicDelegate * mDelegate;

};

#endif // LOGICVIEW_H
