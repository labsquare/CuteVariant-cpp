#include "variantmodel.h"

namespace core {
VariantModel::VariantModel(QObject * parent)
    :QAbstractListModel(parent)
{

}

void VariantModel::setProjet(core::Project *prj)
{
    mPrj = prj;
}

int VariantModel::rowCount(const QModelIndex &parent) const
{

    return mVariants.count();
}

int VariantModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant VariantModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();


    if (role == Qt::DisplayRole)
    {
        if (index.column() == 0)
            return mVariants.at(index.row()).chromosom();

        if (index.column() == 1)
            return mVariants.at(index.row()).position();


        if (index.column() == 2)
            return mVariants.at(index.row()).ref();


        if (index.column() == 3)
            return mVariants.at(index.row()).alt();

    }


    return QVariant();


}

void VariantModel::setQuery(const QString &raw)
{
    qDebug()<<Q_FUNC_INFO<<raw;

    beginResetModel();
    VariantQuery query = VariantQuery::fromString(raw);

    mVariants = mPrj->sqliteManager()->variants(query);

    endResetModel();


}
}
