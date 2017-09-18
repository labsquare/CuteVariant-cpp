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
     void filterItemCreated(FilterItem * item);


private:
    ColumnView * mView;
};

#endif // COLUMNDOCKWIDGET_H
