#ifndef COLUMNVIEW_H
#define COLUMNVIEW_H
#include <QtWidgets>
#include <QSortFilterProxyModel>
#include "columnmodel.h"
#include "cutevariant.h"
#include "filterdialog.h"
#include "conditionitem.h"

class ColumnView : public QTreeView
{
    Q_OBJECT
public:
    ColumnView(QWidget * parent = nullptr);
    QStringList selectedColumns() const;
    void load();

public Q_SLOTS:
    void setFilter(const QString& txt);

Q_SIGNALS:
    void filterItemCreated(ConditionItem * item);
    void itemChanged();

protected:
    virtual void contextMenuEvent(QContextMenuEvent * event);

private:
    ColumnModel * mModel;
    QSortFilterProxyModel * mProxyModel;
};

#endif // COLUMNVIEW_H
