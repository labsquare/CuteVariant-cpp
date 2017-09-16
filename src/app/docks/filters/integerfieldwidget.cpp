#include "integerfieldwidget.h"

IntegerFieldWidget::IntegerFieldWidget(QWidget *parent)
    :AbstractFieldWidget(parent)
{
    mSpinBox = new QSpinBox;
    mSlider  = new QSlider(Qt::Horizontal);

    mSpinBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->addWidget(mSpinBox);
    vLayout->addWidget(mSlider);

    vLayout->setContentsMargins(0,0,0,0);
    setLayout(vLayout);


    connect(mSpinBox,SIGNAL(valueChanged(int)),this,SLOT(valueChanged(int)));
    connect(mSlider,SIGNAL(valueChanged(int)),this,SLOT(valueChanged(int)));


}

QVariant IntegerFieldWidget::value() const
{
    return mSpinBox->value();
}

void IntegerFieldWidget::setValue(const QVariant &value)
{
    mSpinBox->setValue(value.toInt());
}

void IntegerFieldWidget::setRange(int min, int max)
{
    mSpinBox->setRange(min,max);
    mSlider->setRange(min,max);
}

void IntegerFieldWidget::valueChanged(int value)
{


    if (sender() == mSpinBox)
        mSlider->setValue(value);

    if (sender() == mSlider)
        mSpinBox->setValue(value);



}
