#ifndef BETWEENFIELDWIDGET_H
#define BETWEENFIELDWIDGET_H

#include "abstractfieldwidget.h"

class RangeFieldWidget : public AbstractFieldWidget
{
public:
    RangeFieldWidget(QWidget * parent = nullptr);


    QVariant value() const override;
    void setValue(const QVariant& value) override;

private:
    QSpinBox * mMinBox;
    QSpinBox * mMaxBox;

};

#endif // BETWEENFIELDWIDGET_H
