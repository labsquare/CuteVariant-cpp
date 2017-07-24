#include "tablemodel.h"

TableModel::TableModel(core::Project *prj, QObject *parent)
    :QAbstractListModel(parent)
{
    mPrj = prj;
    //load();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return mDatas.count();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if ( role == Qt::DisplayRole)
    {
        if (index.column() == 0 )
            return mDatas.keys().at(index.row());

        if (index.column() == 1)
            return mDatas.values().at(index.row());
    }

    return QVariant();


}

void TableModel::load()
{
    beginResetModel();

    mDatas = mPrj->sqliteManager()->tables();

    endResetModel();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            if ( section == 0)
                return tr("Table");

            if (section == 1)
                return tr("Count");
        }
    }

    return QVariant();
}
