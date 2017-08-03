#include "annotationconditionpage.h"

AnnotationConditionPage::AnnotationConditionPage(QWidget *parent) : QWidget(parent)
{

    mFieldbox     = new QComboBox;
    mDescription  = new QLabel;
    mOperatorBox  = new QComboBox;
    mValueWidget  = nullptr;

    mOperatorBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    mFormLayout = new QFormLayout;
    mFormLayout->addRow("fields",mFieldbox);
    mFormLayout->addRow("operator",mOperatorBox);
    mFormLayout->addRow("value",new QWidget);


    mFormLayout->setFormAlignment(Qt::AlignTop|Qt::AlignHCenter);


    mDescription->setWordWrap(true);

    setLayout(mFormLayout);


    setWindowTitle("Annotation fields");

    loadFields();

    // see Qt documentation for this syntax
    connect(mFieldbox, SIGNAL(activated(int)),this,SLOT(loadOperators()));
    connect(mOperatorBox, SIGNAL(activated(int)),this,SLOT(loadForm()));


}

ConditionalItem *AnnotationConditionPage::toItem() const
{

    return new ConditionalItem(mFields[mFieldbox->currentIndex()],
                               Operator::Type(mOperatorBox->currentData().toInt()),
                               mValueWidget->value()
                               );

}

void AnnotationConditionPage::fromItem(ConditionalItem *item)
{
    qDebug()<<item->field().name();

    mFieldbox->setCurrentText(item->field().name().toUpper());
    loadOperators();
    mOperatorBox->setCurrentText(Operator::name(item->operatorType()).toUpper());
    loadForm();
    mValueWidget->setValue(item->value());

}

void AnnotationConditionPage::loadFields()
{

    mFieldbox->clear();
    mFields =  cutevariant->sqliteManager()->fields();
    for (cvar::Field f : mFields)
        mFieldbox->addItem(f.name().toUpper(),f.id());


    loadOperators();
}

void AnnotationConditionPage::loadOperators()
{
    mOperatorBox->clear();
    for (Operator::Type type : ConditionFieldFactory::operatorsList(mFields[mFieldbox->currentIndex()]))
        mOperatorBox->addItem(Operator::name(type).toUpper(), int(type));

    loadForm();

}
void AnnotationConditionPage::loadForm()
{
    // delete
    mFormLayout->removeRow(2);

    mValueWidget = nullptr;


    if (mOperatorBox->currentData() == int(Operator::In))
        mValueWidget = new ListFieldWidget;

    if (mOperatorBox->currentData() == int(Operator::Between))
        mValueWidget = new RangeFieldWidget;

    if (mValueWidget == nullptr)
        mValueWidget = ConditionFieldFactory::widget(mFields[mFieldbox->currentIndex()]);


    // the method avaible from Qt 5.8
    mFormLayout->insertRow(2,"Value", mValueWidget);

}


