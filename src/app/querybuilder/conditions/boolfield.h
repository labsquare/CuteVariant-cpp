#ifndef BOOLFIELD_H
#define BOOLFIELD_H
#include <QtWidgets>
#include "abstractfield.h"

class BoolField : public AbstractField
{
public:
    BoolField(QWidget * parent = nullptr);
    QVariant value() const override;
    void setValue(const QVariant& value) override;

private:
    QComboBox * mBox;
};

#endif // BOOLFIELD_H
