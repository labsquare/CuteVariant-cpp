#include "rangefieldwidget.h"

RangeFieldWidget::RangeFieldWidget(QWidget *parent)
    :AbstractFieldWidget(parent)
{
    mMinBox = new QSpinBox;
    mMaxBox = new QSpinBox;

    QHBoxLayout * hLayout = new QHBoxLayout;
    hLayout->addWidget(mMinBox);
    hLayout->addWidget(mMaxBox);
    hLayout->setContentsMargins(0,0,0,0);

    setLayout(hLayout);

}

QVariant RangeFieldWidget::value() const
{

    return QPoint(mMinBox->value(), mMaxBox->value());

}

void RangeFieldWidget::setValue(const QVariant &value)
{

    mMinBox->setValue(value.toPoint().x());
    mMaxBox->setValue(value.toPoint().y());
}
