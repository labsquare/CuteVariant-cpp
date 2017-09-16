#ifndef LISTFIELD_H
#define LISTFIELD_H
#include <QtWidgets>
#include "abstractfieldwidget.h"

class ListFieldWidget : public AbstractFieldWidget
{
    Q_OBJECT
public:
    ListFieldWidget(QWidget * parent = nullptr);
    QVariant value() const override;
    void setValue(const QVariant& value) override;

protected Q_SLOTS:
    void add();
    void rem();


private:
   QListWidget * mView;

};

#endif // LISTFIELD_H
