#ifndef BOOLFIELD_H
#define BOOLFIELD_H
#include <QtWidgets>
#include "abstractfieldwidget.h"

class BoolField : public AbstractFieldWidget
{
public:
    BoolField(QWidget * parent = nullptr);
    QVariant value() const override;
    void setValue(const QVariant& value) override;

private:
    QComboBox * mBox;
};

#endif // BOOLFIELD_H
