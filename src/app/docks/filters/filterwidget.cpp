#include "filterwidget.h"

FilterWidget::FilterWidget(QWidget *parent) : QWidget(parent)
{

    resize(400,200);

    mNameLabel   = new QLabel("<b>Gene Name (INTEGER) </b>");
    mDescLabel   = new QLabel("Description tu trucDescription tu truDescription tu truDescription tu truDescription tu tru");
    mOperatorBox = new QComboBox();
    mDescLabel->setWordWrap(true);

    QVBoxLayout * mainLayout = new QVBoxLayout;

    mFormLayout = new QFormLayout;
    mFormLayout->addRow("Operation", mOperatorBox);

    QGroupBox * filterGroup = new QGroupBox;
    filterGroup->setTitle("Create a filter");
    filterGroup->setLayout(mFormLayout);


    mainLayout->addWidget(mNameLabel);
    mainLayout->addWidget(mDescLabel);
    mainLayout->addWidget(filterGroup);

    setLayout(mainLayout);
    mainLayout->setAlignment(Qt::AlignLeft|Qt::AlignTop);

    mOperatorBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    filterGroup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(mOperatorBox, SIGNAL(activated(int)),this,SLOT(operatorChanged()));

}
//----------------------------------------------------------------------------
void FilterWidget::setField(const cvar::Field &field)
{
    mField = field;
    mNameLabel->setText(QString("<b>%1 (%2)</b>").arg(field.name(),field.typeName()));
    mDescLabel->setText(field.description());

    mOperatorBox->clear();
    for (Operator::Type op : FilterFieldFactory::operatorsList(field))
    {
        mOperatorBox->addItem(QString("%1").arg(Operator::symbol(op)), op);
        mOperatorBox->setItemData(mOperatorBox->count()-1,  Operator::name(op), Qt::ToolTipRole);
    }

    operatorChanged();
}
//----------------------------------------------------------------------------
const cvar::Field &FilterWidget::field() const
{
    return mField;
}
//----------------------------------------------------------------------------
QVariant FilterWidget::value() const
{
    if (mFormLayout)
        return mFieldWidget->value();

    return QVariant();
}
//----------------------------------------------------------------------------
void FilterWidget::setValue(const QVariant &value)
{
    mFieldWidget->setValue(value);
}
//----------------------------------------------------------------------------
Operator::Type FilterWidget::currentOperator() const
{
    return Operator::Type(mOperatorBox->currentData().toInt());

}
//----------------------------------------------------------------------------

void FilterWidget::setCurrentOperator(Operator::Type type)
{
    mOperatorBox->setCurrentText(Operator::name(type));
}
//----------------------------------------------------------------------------

ConditionItem *FilterWidget::createCondition() const
{
    ConditionItem * item = new ConditionItem(field(), currentOperator(), value());
    return item;

}
//----------------------------------------------------------------------------

void FilterWidget::operatorChanged()
{
    qDebug()<<"operator changed";

    mFormLayout->removeRow(1);



    if (currentOperator() == Operator::Between){
        mFieldWidget = new RangeFieldWidget;
        mFormLayout->insertRow(1,"value", mFieldWidget);
        return;
    }

    if (currentOperator() == Operator::In){
        mFieldWidget = new ListFieldWidget;
        mFormLayout->insertRow(1,"value", mFieldWidget);
        return;
    }

    mFieldWidget = FilterFieldFactory::widget(mField);
    mFormLayout->insertRow(1,"value",mFieldWidget);


}
