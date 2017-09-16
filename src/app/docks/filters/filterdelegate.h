#ifndef LOGICDELEGATE_H
#define LOGICDELEGATE_H
#include <QStyledItemDelegate>
#include <QComboBox>
#include <QPainter>
#include "filtermodel.h"


class FilterDelegate : public QStyledItemDelegate
{
public:
    FilterDelegate(QObject * parent = nullptr);
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};

#endif // LOGICDELEGATE_H
