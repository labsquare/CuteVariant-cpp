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
    void addCondition(FilterItem * item);
    void addCondition();
    void addLogic();
    void remove();


private:
    FilterView * mView;
};

#endif // CONDITIONDOCKWIDGET_H
