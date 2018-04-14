#include "samplemodel.h"
namespace cvar {
SampleModel::SampleModel(Project *prj, QObject * parent )
    :QAbstractListModel(parent)
{
    mProject = prj;
    load();

}

int SampleModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mDatas.count();
}

int SampleModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

QVariant SampleModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();


    if (role == Qt::DisplayRole)
    {
        if (index.column() == 0)
        return mDatas[index.row()].name();
    }

    return QVariant();

}

void SampleModel::load()
{
    beginResetModel();

    mDatas = mProject->sqlite()->samples();

    endResetModel();
}
}
