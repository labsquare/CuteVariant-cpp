#include "filterdialog.h"

FilterDialog::FilterDialog(QWidget * parent)
    :QDialog(parent)
{

    mWidget  = new FilterWidget;
    QDialogButtonBox * buttons = new QDialogButtonBox(QDialogButtonBox::Cancel|QDialogButtonBox::Save);
    resize(400,200);

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mWidget);
    mainLayout->addWidget(buttons);

    mWidget->layout()->setContentsMargins(0,0,0,0);

    setLayout(mainLayout);

    connect(buttons,SIGNAL(accepted()),this,SLOT(accept()));
    connect(buttons,SIGNAL(rejected()),this,SLOT(reject()));
}

void FilterDialog::setField(const cvar::Field &field)
{

    mWidget->setField(field);

}

const cvar::Field &FilterDialog::field() const
{
    return mWidget->field();
}

void FilterDialog::setValue(const QVariant &value)
{
    mWidget->setValue(value);
}

QVariant FilterDialog::value() const
{
    return mWidget->value();
}

void FilterDialog::setCurrentOperator(Operator::Type type)
{
    mWidget->setCurrentOperator(type);
}

Operator::Type FilterDialog::currentOperator()
{
    return mWidget->currentOperator();
}

ConditionItem *FilterDialog::createCondition() const
{
    return mWidget->createCondition();
}
