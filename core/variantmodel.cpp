#include "variantmodel.h"

VariantModel::VariantModel( QObject *parent)
    :QAbstractTableModel(parent)
{
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
            if (annId < mVariants.at(index.row()).annotationCount())
            {
               // qDebug()<< mVariants.at(index.column()).annotation(0).second;

                return mVariants.at(index.row()).annotation(annId).second;
            }

        }

    }

    return QVariant();

}

QVariant VariantModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            if (mVariants.isEmpty())
                return QVariant();

            if (section == ChromCol)
                return "Chromosom";

            if (section == PosCol)
                return "Position";

            if (section == RefCol)
                return "Ref";

            if (section == AltCol)
                return "Alt";

            if (section >= AnnCol)
            {
                int annId = section- 4;
                if (annId < mVariants.first().annotationCount())
                {
                    return mVariants.first().annotation(annId).first;
                }
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

    QSqlQuery query = Project::variantQuery(mAnnotationColumns);

    if (!query.exec()){
        qDebug()<<query.lastError().text();
        return;
    }

    beginResetModel();
    mVariants.clear();

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
            //qDebug()<<query.record().value(i);


        }


    }


    endResetModel();


}


