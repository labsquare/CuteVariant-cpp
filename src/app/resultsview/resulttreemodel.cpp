#include "resulttreemodel.h"



ResultTreeModel::ResultTreeModel( QObject *parent)
    :QAbstractItemModel(parent)
{
}

ResultTreeModel::~ResultTreeModel()
{

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

    return 0;
}
//---------------------------------------------------------------------------

int ResultTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

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

    //    if (role == Qt::DecorationRole)
    //    {
    //            if (index.column() == 0 && index.parent() != QModelIndex())
    //           return FIcon(0xf60d);


    //    }



    return QVariant() ;
}
//---------------------------------------------------------------------------
QVariant ResultTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {

        if (orientation == Qt::Horizontal)
            return mRecords.first().fieldName(section+1);

    }

    return QVariant();

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

    //    if (parent == QModelIndex())
    //        return ;

    //    int count       = mRecords[parent.row()].value("count").toInt();
    //    int parentRow   = parent.row();
    //    QStringList ids = mRecords[parent.row()].value("childs").toString().split(",");


    //    qDebug()<<ids;

    //    beginInsertRows(parent,0, count-1);
    //    mChilds[parentRow].clear();

    //    cvar::VariantQuery temp = mCurrentQuery;
    //    temp.setCondition(QString("%2.id IN (%1)").arg(ids.join(",")).arg(mCurrentQuery.table()));
    //    temp.setGroupBy({});
    //    temp.setNoLimit();

    //    QSqlQuery query = QSqlQuery(temp.toSql());

    //    while (query.next())
    //    {
    //        mChilds[parentRow].append(query.record());
    //    }


    //    qDebug()<<query.lastError().text();
    //    qDebug()<<query.lastQuery();

    //    endInsertRows();
}
//---------------------------------------------------------------------------
void ResultTreeModel::sort(int column, Qt::SortOrder order)
{

    if (column < columnCount()) {

        //QString col = headerData(column, Qt::Horizontal, Qt::DisplayRole).toString();
        // TODO: hack remove.. It's hugly
        // column + 1 because we hide ID
        // remove "sql 'as name' statement "
        QString col = mCurrentQuery.columns().at(column+1);

        mCurrentQuery.clearSortColumns();
        mCurrentQuery.addSortColumns(col, order);
        load();
    }

}


//---------------------------------------------------------------------------
void ResultTreeModel::setQuery(const cvar::VariantQuery &q)
{
    mCurrentQuery = q ;
}
//---------------------------------------------------------------------------

QSqlRecord ResultTreeModel::record(const QModelIndex &index)
{
    if (!index.isValid())
        return QSqlRecord();

    if ( index.parent() == QModelIndex())
        return mRecords.at(index.row());

    if ( index.parent().parent() == QModelIndex())
        return mChilds[index.parent().row()].at(index.row());

    return QSqlRecord();

}
//---------------------------------------------------------------------------
const cvar::VariantQuery &ResultTreeModel::currentQuery() const
{
    return mCurrentQuery;
}
//---------------------------------------------------------------------------
bool ResultTreeModel::exportCsv(const QString &filename) const
{

    //    QFile file(filename);
    //    if (file.open(QIODevice::WriteOnly))
    //    {
    //            QTextStream stream(&file);

    //            cvar::VariantQuery vquery = mCurrentQuery;
    //            vquery.setNoLimit();
    //            QSqlQuery query (vquery.toSql());
    //            qDebug()<<query.lastError().text();
    //            qDebug()<<query.lastQuery();

    //            bool header = false;

    //            // save query ( -2 ) to avoid count and childs
    //            while (query.next()){

    //                // save header
    //                if (!header)
    //                {
    //                    stream <<"#";
    //                    for (int col = 0; col < query.record().count() - 2; ++col)
    //                    {
    //                        stream <<query.record().fieldName(col)<<"\t";
    //                    }
    //                    stream <<"\n";
    //                    header = true;
    //                }

    //                // save record
    //                for (int col = 0; col < query.record().count() -2 ; ++col)
    //                {
    //                    stream << query.record().value(col).toString() <<"\t";
    //                }
    //                stream <<"\n";


    //            }
    //            qDebug()<<Q_FUNC_INFO<<" export completed";
    //            return true;
    //    }
    //    return false;
}
//---------------------------------------------------------------------------
bool ResultTreeModel::isEmpty() const
{
    return mRecords.isEmpty();
}

//---------------------------------------------------------------------------
void ResultTreeModel::load()
{
    beginResetModel();
    mRecords.clear();
    mChilds.clear();

    QSqlQuery query(mCurrentQuery.toSql());
    qDebug()<<query.lastError().text();
    qDebug()<<query.lastQuery();

    while (query.next())
        mRecords.append(query.record());
    endResetModel();
}
//---------------------------------------------------------------------------
void ResultTreeModel::load(int offset, int limit)
{
        mCurrentQuery.setOffset(offset);
        mCurrentQuery.setLimit(limit);
        load();
}
