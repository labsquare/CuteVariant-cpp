#ifndef LOGICDELEGATE_H
#define LOGICDELEGATE_H
#include <QStyledItemDelegate>

class LogicDelegate : public QStyledItemDelegate
{
public:
    LogicDelegate(QObject * parent = nullptr);

    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;


};

#endif // LOGICDELEGATE_H
