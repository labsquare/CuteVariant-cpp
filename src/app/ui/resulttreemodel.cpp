#include "resulttreemodel.h"



ResultTreeModel::ResultTreeModel(core::Project *prj, QObject *parent)
    :QAbstractItemModel(parent)
{
    mProject = prj;
}
//---------------------------------------------------------------------------

QModelIndex ResultTreeModel::index(int row, int column, const QModelIndex &parent) const
{

    if (!hasIndex(row,column,parent))
        return QModelIndex();

    return createIndex(row,column, parent.row());

}
//---------------------------------------------------------------------------

QModelIndex ResultTreeModel::parent(const QModelIndex &child) const
{

    if (!child.isValid())
        return QModelIndex();

    int parentRow = child.internalId();

    return index(parentRow,0,QModelIndex());

}
//---------------------------------------------------------------------------

int ResultTreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent == QModelIndex())
        return mRecords.count();

    //    // second level
    if (parent.parent() == QModelIndex())
        return mChilds[parent.row()].count();

    //    return 0;
}
//---------------------------------------------------------------------------

int ResultTreeModel::columnCount(const QModelIndex &parent) const
{
    if (mRecords.isEmpty())
        return 0;


    return mRecords.first().count() - 2;

}
//---------------------------------------------------------------------------

QVariant ResultTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        if (index.parent() == QModelIndex()){
            QSqlRecord rec = mRecords[index.row()];
            return rec.value(index.column());
        }

        if (index.parent().parent() == QModelIndex())
        {
            QSqlRecord rec = mChilds[index.parent().row()][index.row()];
            return rec.value(index.column());


        }
    }
    return QVariant() ;
}
//---------------------------------------------------------------------------

bool ResultTreeModel::hasChildren(const QModelIndex &parent) const
{
    if (parent == QModelIndex())
        return true;

    // second level
    if (parent.parent() == QModelIndex())
        return mRecords[parent.row()].value("count").toInt() > 1;

    return false;
}
//---------------------------------------------------------------------------

bool ResultTreeModel::canFetchMore(const QModelIndex &parent) const
{
    if (parent == QModelIndex())
        return false;

    if (parent.parent() == QModelIndex())
        return mRecords[parent.row()].value("count").toInt() > 1;

    return false;
}
//---------------------------------------------------------------------------

void ResultTreeModel::fetchMore(const QModelIndex &parent)
{

    if (parent == QModelIndex())
        return ;


    int count       = mRecords[parent.row()].value("count").toInt();
    int parentRow   = parent.row();
    QStringList ids = mRecords[parent.row()].value("childs").toString().split(",");

    qDebug()<<"childs"<<ids;

    beginInsertRows(parent,0, count-1);
    mChilds[parentRow].clear();

    QSqlQuery query(QString("SELECT id, chr, pos, ref, alt, ANN_FEATURE_ID FROM variants WHERE id IN (%1)").arg(ids.join(",")));
    while (query.next())
    {
        mChilds[parentRow].append(query.record());
        qDebug()<<"add "<<query.record();
    }


    qDebug()<<query.lastError().text();
    qDebug()<<query.lastQuery();



    endInsertRows();


}
//---------------------------------------------------------------------------
void ResultTreeModel::load()
{
    beginResetModel();
    mRecords.clear();
    QSqlQuery query;
    query.exec("SELECT id, chr, pos, ref, alt, ANN_FEATURE_ID, COUNT(id) as 'count', group_concat(id) as 'childs' FROM variants GROUP BY chr,pos,ref, alt LIMIT 100");


    while (query.next())
    {
        qDebug()<<"record" <<query.record().value("chr")<<" "<<query.record().value("count").toInt();
        mRecords.append(query.record());

    }

    qDebug()<<"populate "<<mRecords.size();

    endResetModel();
}
