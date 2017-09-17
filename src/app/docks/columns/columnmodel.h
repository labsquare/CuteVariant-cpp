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
    QList<cvar::Field> selectedFields() const;
    const cvar::Field field(const QModelIndex& index) const;
    void setCheckBox(bool enabled);

protected Q_SLOTS:
    void itemCheckChanged(QStandardItem *item);

protected:
    QStandardItem *createCategory(const QString& name, const QString& description = QString());
    QStandardItem *createField(const cvar::Field& field);


private:
QHash<QString, QStandardItem*> mCategoriesItems;
QStandardItem * mSampleItem;
QList<QPair<QStandardItem*,cvar::Field>> mFieldItems;
bool mHasCheckbox = true; // Columns and filter use this model


};

#endif // COLUMNMODEL_H
