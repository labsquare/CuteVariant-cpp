#include "fieldsmodel.h"

namespace core {
FieldsModel::FieldsModel(Project * prj, QObject * parent)
    :QAbstractListModel(parent)
{

    mProject = prj;

    load();
}

int FieldsModel::rowCount(const QModelIndex &parent) const
{
    return mDatas.count();
}

int FieldsModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant FieldsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {

        if (index.column() == 0)
            return mDatas[index.row()].name();

        if (index.column() == 1)
            return mDatas[index.row()].description();


    }


    return QVariant();

}

void FieldsModel::load()
{
    beginResetModel();

    mDatas = mProject->sqliteManager()->fields();


    endResetModel();

}

}
