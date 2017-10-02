#ifndef CONDITIONALITEM_H
#define CONDITIONALITEM_H
#include <QTreeWidgetItem>
#include "operator.h"
#include "filtermodel.h"
#include "field.h"

class ConditionItem : public QTreeWidgetItem
{
public:
    enum CustomRole{
        FieldRole = Qt::UserRole + 1,
        OperatorRole,
        ValueRole,
        ConditionRole
    };

    ConditionItem(const cvar::Field& field, Operator::Type op, const QVariant& value);

    void setField(const cvar::Field& f);
    void setOperator(Operator::Type op);
    void setValue(const QVariant& value);


    const cvar::Field& field() const;
    QString operatorName() const;
    Operator::Type currentOperator() const;
    QVariant value() const;
    QString expression() const;


protected:
    void updateItem();

private:
    cvar::Field mField;
    Operator::Type mOperator;
    QVariant mValue;


};



#endif // CONDITIONALITEM_H
