#ifndef LISTFIELD_H
#define LISTFIELD_H
#include <QtWidgets>
#include "abstractfield.h"

class ListField : public AbstractField
{
    Q_OBJECT
public:
    ListField(QWidget * parent = nullptr);
    QVariant value() const override;
    void setValue(const QVariant& value) override;

protected Q_SLOTS:
    void add();
    void rem();


private:
   QListWidget * mView;

};

#endif // LISTFIELD_H
