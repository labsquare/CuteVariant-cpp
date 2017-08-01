#include "doublefield.h"

DoubleField::DoubleField(QWidget *parent)
    :AbstractField(parent)
{
    mSpinBox = new QDoubleSpinBox;
    mSlider  = new QSlider;

    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->addWidget(mSpinBox);
    vLayout->addWidget(mSlider);

    vLayout->setContentsMargins(0,0,0,0);


    setLayout(vLayout);


}

QVariant DoubleField::value() const
{
    return mSpinBox->value();
}

void DoubleField::setValue(const QVariant &value)
{
    mSpinBox->setValue(value.toInt());
}

void DoubleField::setRange(double min, double max)
{
    mSpinBox->setRange(min,max);
    mSlider->setRange(min,max);
}
