#ifndef COLUMNMODEL_H
#define COLUMNMODEL_H
#include <QStandardItemModel>
#include "field.h"
#include "sample.h"
#include "project.h"

class ColumnModel : public QStandardItemModel
{
    Q_OBJECT
public:
    ColumnModel( QObject * parent = nullptr);
    void load();

    QStringList selectedColumns() const;

protected Q_SLOTS:
    void itemCheckChanged(QStandardItem *item);

protected:
    QStandardItem *createItem(const QString& name,
                              const QString& description,
                              const QString& colname = QString());


private:

QStandardItem * mVariantItem;
QStandardItem * mAnnotationItem;
QStandardItem * mSampleItem;
QStandardItem * mExtraItem;




};

#endif // COLUMNMODEL_H
