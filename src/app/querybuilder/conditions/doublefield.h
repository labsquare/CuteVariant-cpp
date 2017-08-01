#ifndef DOUBLEFIELD_H
#define DOUBLEFIELD_H
#include <QtWidgets>
#include "abstractfield.h"

class DoubleField : public AbstractField
{
public:
    DoubleField(QWidget * parent = nullptr);
    QVariant value() const override;
    void setValue(const QVariant& value) override;

    void setRange(double min, double max);
private:
    QDoubleSpinBox * mSpinBox;
    QSlider * mSlider;
};

#endif // DOUBLEFIELD_H
