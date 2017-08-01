#include "annotationconditionpage.h"

AnnotationConditionPage::AnnotationConditionPage(QWidget *parent) : QWidget(parent)
{

    mFieldbox = new QComboBox;
    mDescription = new QLabel;


    QComboBox * test1 = new QComboBox;
    QSpinBox * test2  = new QSpinBox;

    test2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    mFormLayout = new QFormLayout;
    mFormLayout->addRow("fields",mFieldbox);
    mFormLayout->addRow("operator",test1);
    mFormLayout->addRow("value",new ListField);


    mFormLayout->setFormAlignment(Qt::AlignVCenter|Qt::AlignCenter);


    mDescription->setWordWrap(true);

    setLayout(mFormLayout);


    setWindowTitle("Annotation fields");

    loadFields();

    // see Qt documentation for this syntax
    connect(mFieldbox, SIGNAL(currentIndexChanged(int)),this,SLOT(fieldChanged(int)));

}

void AnnotationConditionPage::loadFields()
{

    mFieldbox->clear();
    mFields =  cutevariant->sqliteManager()->fields();
    for (cvar::Field f : mFields)
        mFieldbox->addItem(f.name(),f.id());


}

void AnnotationConditionPage::fieldChanged(int index)
{

    // avaible from Qt 5.8
    mFormLayout->removeRow(2);
    mFormLayout->insertRow(2,"Value", ConditionFieldFactory::widget(mFields[index]));



}
