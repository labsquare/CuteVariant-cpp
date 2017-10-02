#ifndef CONDITIONDOCKWIDGET_H
#define CONDITIONDOCKWIDGET_H
#include "basedockwidget.h"
#include "filterview.h"
#include "allfilterdialog.h"
//TODO : rename everything as FilterDockWidget

class FilterDockWidget : public BaseDockWidget
{
    Q_OBJECT
public:
    FilterDockWidget(QWidget * parent = 0);
    QString condition() const;


public Q_SLOTS:
    void addCondition(ConditionItem * item);
    void addCondition();
    void addLogic();
    void remove();

protected Q_SLOTS:
    void updateActions();


private:
    FilterView * mView;
    QAction * mAddConditionAction;
    QAction * mAddLogicAction;
    QAction * mRemAction;


};

#endif // CONDITIONDOCKWIDGET_H
