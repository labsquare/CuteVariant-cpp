#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QAbstractListModel>
#include "project.h"


class TableModel : public QAbstractListModel
{
public:
    TableModel(core::Project * prj, QObject * parent = 0);
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void load();

private:
    core::Project * mPrj;
    QHash<QString, int> mDatas; // table name, count
};

#endif // TABLEMODEL_H
