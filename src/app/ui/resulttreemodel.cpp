#include "resulttreemodel.h"



ResultTreeModel::ResultTreeModel(QObject *parent)
    :QAbstractItemModel(parent)
{

}

QModelIndex ResultTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row,column,parent))
        return QModelIndex();


    return createIndex(row,column);
}

QModelIndex ResultTreeModel::parent(const QModelIndex &child) const
{
    return QModelIndex();

}

int ResultTreeModel::rowCount(const QModelIndex &parent) const
{
    return 0;
}

int ResultTreeModel::columnCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant ResultTreeModel::data(const QModelIndex &index, int role) const
{
    return QVariant() ;
}

bool ResultTreeModel::hasChildren(const QModelIndex &parent) const
{
    return false;
}

bool ResultTreeModel::canFetchMore(const QModelIndex &parent) const
{
    return false;
}

void ResultTreeModel::fetchMore(const QModelIndex &parent)
{

}
