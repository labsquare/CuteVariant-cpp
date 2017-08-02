#include "boolfield.h"

BoolField::BoolField(QWidget *parent)
    :AbstractFieldWidget(parent)
{

    mBox = new QComboBox;

    mBox->addItems({"False","True"});

    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(0,0,0,0);
    vLayout->addWidget(mBox);

}

QVariant BoolField::value() const
{
    return (bool)(mBox->currentIndex());
}

void BoolField::setValue(const QVariant &value)
{
    mBox->setCurrentIndex(value.toInt());
}
