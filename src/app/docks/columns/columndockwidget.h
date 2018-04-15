#ifndef COLUMNDOCKWIDGET_H
#define COLUMNDOCKWIDGET_H
#include "basedockwidget.h"
#include "columnview.h"

class ColumnDockWidget : public BaseDockWidget
{
    Q_OBJECT
public:
    ColumnDockWidget(QWidget * parent = 0);
     QStringList selectedColumns() const;

public Q_SLOTS:
     void reset() override;

Q_SIGNALS:
     void filterItemCreated(ConditionItem * item);



private:
    ColumnView * mView;
    QLineEdit * mSearchEdit;

};

#endif // COLUMNDOCKWIDGET_H
