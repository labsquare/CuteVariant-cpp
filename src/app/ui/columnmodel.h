#ifndef COLUMNMODEL_H
#define COLUMNMODEL_H
#include <QStandardItemModel>
#include "project.h"
#include "field.h"
#include "sample.h"

class ColumnModel : public QStandardItemModel
{
    Q_OBJECT
public:
    ColumnModel(core::Project * prj, QObject * parent = nullptr);
    void load();

    QStringList selectedColumns() const;

protected Q_SLOTS:
    void itemCheckChanged(QStandardItem *item);

protected:
    QStandardItem *createItem(const QString& name,
                              const QString& description,
                              const QString& colname = QString());


private:

core::Project * mProject;
QStandardItem * mVariantItem;
QStandardItem * mAnnotationItem;
QStandardItem * mSampleItem;
QStandardItem * mExtraItem;




};

#endif // COLUMNMODEL_H
