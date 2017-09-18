#ifndef COLUMNVIEW_H
#define COLUMNVIEW_H
#include <QtWidgets>
#include "columnmodel.h"
#include "project.h"
#include "filterdialog.h"
#include "filteritem.h"

class ColumnView : public QTreeView
{
    Q_OBJECT
public:
    ColumnView(QWidget * parent = nullptr);
    QStringList selectedColumns() const;
    void load();

Q_SIGNALS:
    void filterItemCreated(FilterItem * item);

protected:
    virtual void contextMenuEvent(QContextMenuEvent * event);

private:
    ColumnModel * mModel;
};

#endif // COLUMNVIEW_H
