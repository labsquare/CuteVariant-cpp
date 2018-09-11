#include "variantdatamapper.h"

namespace cvar {
VariantDataMapper::VariantDataMapper()
    :DataMapper<Variant, VariantDataMapper>("variants")
{

    addColumn("chr",DataColumn::Text, "NOT NULL");
    addColumn("pos",DataColumn::Integer, "NOT NULL");
    addColumn("ref",DataColumn::Text);
    addColumn("alt",DataColumn::Text);
    addColumn("favoris",DataColumn::Integer);
    addColumn("score",DataColumn::Integer);
    addColumn("comment",DataColumn::Text);

}

Variant VariantDataMapper::fromSql(const QSqlRecord &record) const
{

    Variant variant;
    variant.setChr(record.value("chr").toString());
    variant.setPos(record.value("pos").toInt());
    variant.setRef(record.value("ref").toString());
    variant.setAlt(record.value("alt").toString());
    variant.setFavoris(record.value("favoris").toBool());
    variant.setScore(record.value("score").toInt());
    variant.setComment(record.value("comment").toString());

    return variant;

}

QHash<QString, QVariant> VariantDataMapper::toSql(const Variant &record) const
{
    QHash<QString, QVariant> b;

    b["chr"]     = record.chromosom();
    b["pos"]     = record.position();
    b["ref"]     = record.ref();
    b["alt"]     = record.alt();
    b["favoris"] = record.isFavoris();
    b["score"]   = record.score();
    b["comment"] = record.comment();

    for (const Field& f : mDynamicFields){
//        qDebug()<<"COLNAME"<<f.colname();
//        qDebug()<<"KEYS"<<record.annotations().keys();

        b[f.colname()] = record.annotation(f.colname());

    }

    return b;

}


void VariantDataMapper::setDynamicFields(const QList<Field> &dynamicFields)
{
    mDynamicFields = dynamicFields;

    for (const Field& f : mDynamicFields)
        addColumn(f.colname(), DataColumn::typeFromQt(f.type()));

}
}
