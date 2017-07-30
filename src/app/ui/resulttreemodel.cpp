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

    return mCurrentQuery.columns().size();

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
            return rec.value(index.column()+1);
        }

        if (index.parent().parent() == QModelIndex())
        {
            QSqlRecord rec = mChilds[index.parent().row()][index.row()];
            return rec.value(index.column()+1);
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


    beginInsertRows(parent,0, count-1);
    mChilds[parentRow].clear();

    core::VariantQuery temp = mCurrentQuery;
    temp.setCondition(QString("variants.id IN (%1)").arg(ids.join(",")));
    temp.setGroupBy({});

    QSqlQuery query = mProject->sqliteManager()->variants(temp);

    while (query.next())
    {
        mChilds[parentRow].append(query.record());
    }


    qDebug()<<query.lastError().text();
    qDebug()<<query.lastQuery();

    endInsertRows();
}
//---------------------------------------------------------------------------
int ResultTreeModel::totalRowCount() const
{
    return mTotalRowCount;
}
//---------------------------------------------------------------------------
void ResultTreeModel::setQuery(const core::VariantQuery &q)
{
    mCurrentQuery = q ;
    mCurrentQuery.setGroupBy({"chr","pos","ref","alt"});

    // compute one time row count
    mTotalRowCount = mProject->sqliteManager()->variantsCount(mCurrentQuery);

    load();
}

//---------------------------------------------------------------------------
void ResultTreeModel::load(int offset, int limit)
{
    beginResetModel();
    mRecords.clear();

    mCurrentQuery.setOffset(offset);
    mCurrentQuery.setLimit(limit);

    QSqlQuery query = mProject->sqliteManager()->variants(mCurrentQuery);
    qDebug()<<query.lastError().text();
    qDebug()<<query.lastQuery();

    while (query.next())
        mRecords.append(query.record());
    endResetModel();
}
