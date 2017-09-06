#ifndef CONDITIONDOCKWIDGET_H
#define CONDITIONDOCKWIDGET_H
#include "basedockwidget.h"
#include "filterview.h"

//TODO : rename everything as FilterDockWidget

class FilterDockWidget : public BaseDockWidget
{
    Q_OBJECT
public:
    FilterDockWidget(QWidget * parent = 0);
    QString condition() const;



private:
    FilterView * mView;
};

#endif // CONDITIONDOCKWIDGET_H
