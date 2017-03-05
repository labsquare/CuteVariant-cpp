#ifndef LOGICDELEGATE_H
#define LOGICDELEGATE_H
#include <QItemDelegate>
#include <QtWidgets>
#include "LogicModel.h"
#include "ConditionWidget.h"

class LogicDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    LogicDelegate(QObject *parent = Q_NULLPTR);

    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setFieldNames(const QStringList& fields);

private:
    QStringList mFieldNames;

};

#endif // LOGICDELEGATE_H
