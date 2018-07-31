#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H
#include <QtWidgets>
#include "cutevariant.h"
#include "filterwidget.h"
#include "conditionitem.h"

class FilterDialog : public QDialog
{
public:
    FilterDialog(QWidget * parent = nullptr);
    void setField(const cvar::Field& field);
    const cvar::Field& field() const;

    void setValue(const QVariant& value);
    QVariant value() const;

    void setCurrentOperator(Operator::Type type);
    Operator::Type currentOperator();

    ConditionItem * createCondition() const;



private:
    FilterWidget * mWidget;
    cvar::Field mField;
};

#endif // FILTERDIALOG_H
