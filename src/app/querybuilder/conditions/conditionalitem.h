#ifndef CONDITIONALITEM_H
#define CONDITIONALITEM_H
#include <QStandardItem>
#include "operator.h"

class ConditionalItem : public QStandardItem
{
public:
    enum CustomRole{
        FieldRole = Qt::UserRole + 1,
        OperatorRole,
        ValueRole
    };

    ConditionalItem(const QString& field, Operator::Type op, const QVariant& value);

    void setField(const QString& f);
    void setOperator(Operator::Type op);
    void setValue(const QVariant& value);

    QString field() const;
    QString operatorName() const;
    Operator::Type operatorType() const;
    QVariant value() const;


protected:
    void updateText();


};



#endif // CONDITIONALITEM_H
