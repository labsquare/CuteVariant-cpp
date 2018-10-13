#ifndef ABSTRACTOBSERVABLEWIDGET_H
#define ABSTRACTOBSERVABLEWIDGET_H
#include <QWidget>
#include "variantquery.h"

class AbstractQueryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractQueryWidget(QWidget *parent = nullptr);

    virtual void readQuery(const cvar::VariantQuery& query) = 0;
    virtual void writeQuery(cvar::VariantQuery& query) = 0;

Q_SIGNALS:
    void changed();



};

#endif // ABSTRACTOBSERVABLEWIDGET_H
