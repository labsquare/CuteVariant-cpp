#ifndef LOGICVIEW_H
#define LOGICVIEW_H
#include <QtWidgets>
#include "logicmodel.h"
#include "project.h"

class LogicView : public QTreeView
{
    Q_OBJECT
public:
    LogicView(core::Project * prj, QWidget * parent = Q_NULLPTR);
    void contextMenuEvent(QContextMenuEvent* event);
    QString query();



private:
    LogicModel * mModel;

    core::Project * mPrj;
};

#endif // LOGICVIEW_H
