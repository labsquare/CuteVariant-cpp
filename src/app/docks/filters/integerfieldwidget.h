#ifndef INTEGERFIELD_H
#define INTEGERFIELD_H
#include <QtWidgets>
#include "abstractfieldwidget.h"

class IntegerFieldWidget : public AbstractFieldWidget
{
    Q_OBJECT
public:
    IntegerFieldWidget(QWidget * parent = nullptr);
    QVariant value() const override;
    void setValue(const QVariant& value) override;
    void setRange(int min, int max);

protected Q_SLOTS:
    void valueChanged(int value);

private:
    QSpinBox * mSpinBox;
    QSlider * mSlider;
};

#endif // INTEGERFIELD_H
