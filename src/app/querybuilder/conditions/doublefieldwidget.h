#ifndef DOUBLEFIELD_H
#define DOUBLEFIELD_H
#include <QtWidgets>
#include "abstractfieldwidget.h"

class DoubleFieldWidget : public AbstractFieldWidget
{
public:
    DoubleFieldWidget(QWidget * parent = nullptr);
    QVariant value() const override;
    void setValue(const QVariant& value) override;

    void setRange(double min, double max);
private:
    QDoubleSpinBox * mSpinBox;
    QSlider * mSlider;
};

#endif // DOUBLEFIELD_H
