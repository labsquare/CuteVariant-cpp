#include "variantmodel.h"

VariantModel::VariantModel(Project *prj, QObject *parent)
    :QAbstractTableModel(parent)
{
    mProject = prj;
}

int VariantModel::rowCount(const QModelIndex &parent) const
{
    return mVariants.count();
}

int VariantModel::columnCount(const QModelIndex &parent) const
{
    if (mVariants.isEmpty())
        return 0;

    return mVariants.first().annotationCount() + 4;
}

QVariant VariantModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {

        if (index.column() == ChromCol)
            return mVariants.at(index.row()).chromosom();

        if (index.column() == PosCol)
            return mVariants.at(index.row()).position();

        if (index.column() == RefCol)
            return mVariants.at(index.row()).ref();

        if (index.column() == AltCol)
            return mVariants.at(index.row()).alt();

        if (index.column() >= AnnCol)
        {
            int annId = index.column() - 4;
            if (annId < mVariants.at(index.column()).annotationCount())
            {
                return mVariants.at(index.column()).annotation(annId).second;
            }

        }

    }

    return QVariant();

}

void VariantModel::setAnnotationColumns(const QStringList &annotationColumns)
{
    mAnnotationColumns = annotationColumns;
}

void VariantModel::update()
{
    qDebug()<<"update";

    QSqlQuery query = makeQuery();
    if (!query.exec()){
        qDebug()<<query.lastError().text();
        return;
    }

    beginResetModel();

    while (query.next())
    {
        QString chrom = query.record().value("chrom").toString();
        quint64 pos   = query.record().value("pos").toInt();
        QString ref = query.record().value("ref").toString();
        QString alt = query.record().value("alt").toString();
        mVariants.append(Variation(chrom,pos,ref,alt));

        for (int i=4; i<query.record().count(); ++i)
        {
            mVariants.last().addAnnotation(query.record().field(i).name(), query.record().value(i));
        }
    }


    endResetModel();


}

QSqlQuery VariantModel::makeQuery()
{
    QString req;

    if (mAnnotationColumns.isEmpty())
        req = QString("SELECT chrom,pos,ref,alt FROM variants");
    else
    {
        req = QString("SELECT chrom,pos,ref,alt,%1 FROM variants "
                      "LEFT JOIN annotations on annotations.variant_id = variants.id"
                      ).arg(mAnnotationColumns.join(","));

    }

    qDebug()<<req;

    return QSqlQuery(req);


}
