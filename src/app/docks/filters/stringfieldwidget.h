#ifndef STRINGFIELD_H
#define STRINGFIELD_H
#include <QWidget>
#include "abstractfieldwidget.h"

class StringFieldWidget : public AbstractFieldWidget
{
public:
    StringFieldWidget(QWidget * parent = nullptr);

    QVariant value() const override;
    void setValue(const QVariant& value);

    void setCompletion(QAbstractItemModel * m);

private:
    QLineEdit * mEdit;
    QCompleter * mCompleter;

};

#endif // STRINGFIELD_H
