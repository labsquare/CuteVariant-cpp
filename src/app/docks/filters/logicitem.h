#ifndef LOGICITEM_H
#define LOGICITEM_H
#include <QStandardItem>
#include "filtermodel.h"
class FilterModel;
class LogicItem : public QStandardItem
{
public:
    LogicItem(const QString& op);
    int type() const override;







};

#endif // LOGICITEM_H
