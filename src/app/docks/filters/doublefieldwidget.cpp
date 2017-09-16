#include "doublefieldwidget.h"

DoubleFieldWidget::DoubleFieldWidget(QWidget *parent)
    :AbstractFieldWidget(parent)
{
    mSpinBox = new QDoubleSpinBox;
    mSlider  = new QSlider(Qt::Horizontal);

    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->addWidget(mSpinBox);
    vLayout->addWidget(mSlider);

    vLayout->setContentsMargins(0,0,0,0);


    setLayout(vLayout);


}

QVariant DoubleFieldWidget::value() const
{
    return mSpinBox->value();
}

void DoubleFieldWidget::setValue(const QVariant &value)
{
    mSpinBox->setValue(value.toInt());
}

void DoubleFieldWidget::setRange(double min, double max)
{
    mSpinBox->setRange(min,max);
    mSlider->setRange(min,max);
}
