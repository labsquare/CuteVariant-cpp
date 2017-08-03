#ifndef CONDITIONALITEM_H
#define CONDITIONALITEM_H
#include <QStandardItem>
#include "operator.h"
#include "filtermodel.h"
#include "field.h"

class FilterModel;
class ConditionalItem : public QStandardItem
{
public:
    enum CustomRole{
        FieldRole = Qt::UserRole + 1,
        OperatorRole,
        ValueRole,
        ConditionRole
    };

    ConditionalItem(const cvar::Field& field, Operator::Type op, const QVariant& value);

    void setField(const cvar::Field& f);
    void setOperator(Operator::Type op);
    void setValue(const QVariant& value);

    int type() const override;

    const cvar::Field& field() const;
    QString operatorName() const;
    Operator::Type operatorType() const;
    QVariant value() const;


protected:
    void updateText();

private:
    cvar::Field mField;


};



#endif // CONDITIONALITEM_H
