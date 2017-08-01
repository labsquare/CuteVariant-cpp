#ifndef ABSTRACTFIELD_H
#define ABSTRACTFIELD_H
#include <QtWidgets>

class AbstractField : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractField(QWidget *parent = 0);

    virtual QVariant value() const = 0;
    virtual void setValue(const QVariant& value) = 0;



};

#endif // ABSTRACTFIELD_H
