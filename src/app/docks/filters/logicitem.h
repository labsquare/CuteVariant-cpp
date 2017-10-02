#ifndef LOGICITEM_H
#define LOGICITEM_H
#include <QTreeWidgetItem>

class LogicItem : public QTreeWidgetItem
{
public:
    enum LogicOperator {
      And,
      Or
    };

    LogicItem(LogicItem::LogicOperator op = LogicOperator::And);

    QString name() const;
    LogicOperator logic() const;
    void setLogic(LogicOperator op);

protected:
    void updateItem();


private:
    LogicItem::LogicOperator mOperator; // only "and" and "or"





};

#endif // LOGICITEM_H
