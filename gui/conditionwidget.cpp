#include "ConditionWidget.h"
#include <QApplication>
ConditionWidget::ConditionWidget(QVariant::Type valueType, QWidget *parent) : QFrame(parent)
{

    mFactory  = new QItemEditorFactory;
    mKeyBox = new QComboBox(parent);
    mCompareOperatorBox = new QComboBox(parent);
    mType = valueType;


    mValueEdit = mFactory->createEditor(valueType, parent);

    mValueEdit->setMaximumWidth(200);
    mCompareOperatorBox->setMaximumWidth(70);
    mKeyBox->setMaximumWidth(200);

    QHBoxLayout * cLayout = new QHBoxLayout;

    mKeyBox->addItem("test");
    mKeyBox->addItem("test");

    for (Operator o : LogicModel::conditionOperators())
        mCompareOperatorBox->addItem(o.symbol.toUpper());


    cLayout->addWidget(mKeyBox);
    cLayout->addWidget(mCompareOperatorBox);
    cLayout->addWidget(mValueEdit);
    cLayout->setContentsMargins(2,2,2,2);


    // hack .. There is a bug.. Frame is transparent and text are displayed behind
    setObjectName("condition");
    setStyleSheet(QString("QFrame#condition{background-color: %1}").arg( qApp->palette(this).highlight().color().name()));


    setLayout(cLayout);



}

 QString ConditionWidget::key()
{
    return mKeyBox->currentText();
}

 QString ConditionWidget::conditionOperator()
{
    return mCompareOperatorBox->currentText();
}

 QVariant ConditionWidget::value()
{

    return mValueEdit->property(mFactory->valuePropertyName(mType));
}

void ConditionWidget::setValue(const QString &key, const QString &compareOperator, const QVariant &value)
{
    mKeyBox->setCurrentText(key);
    mCompareOperatorBox->setCurrentText(compareOperator);
    mValueEdit->setProperty(mFactory->valuePropertyName(mType), value);


}

void ConditionWidget::setFieldNames(const QStringList &fieldNames)
{
    mKeyBox->clear();
    mKeyBox->addItems(fieldNames);
}


