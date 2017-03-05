#ifndef LOGICVIEW_H
#define LOGICVIEW_H
#include <QtWidgets>
#include "logicmodel.h"

class LogicView : public QTreeView
{
    Q_OBJECT
public:
    LogicView(QWidget * parent = Q_NULLPTR);
    void contextMenuEvent(QContextMenuEvent* event);
    QString query();



private:
    LogicModel * mModel;
   // LogicDelegate * mDelegate;
};

#endif // LOGICVIEW_H
