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


protected Q_SLOTS:
    void addCondition();
    void addLogic();


private:
//    FilterView * mView;
};

#endif // CONDITIONDOCKWIDGET_H
