#include "variantdatamapper.h"

namespace cvar {
VariantDataMapper::VariantDataMapper()
    :DataMapper<Variant, VariantDataMapper>("variants")
{

    addColumn("bin",DataColumn::Integer, "NOT NULL");
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
    variant.setBin(record.value("bin").toUInt());
    variant.setChr(record.value("chr").toString());
    variant.setPos(record.value("pos").toUInt());
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

    b["bin"]     = record.bin();
    b["chr"]     = record.chromosom();
    b["pos"]     = record.position();
    b["ref"]     = record.ref();
    b["alt"]     = record.alt();
    b["favoris"] = record.isFavoris();
    b["score"]   = record.score();
    b["comment"] = record.comment();

    // add annotation
    for (const Field& f : mDynamicFields){

        // do not add chr,pos,ref,alt fields which are already set
        if (!mIgnoreField.contains(f.name()))
        {
            b[f.name()] = record.annotation(f.name());
        }
    }

    return b;

}


void VariantDataMapper::setDynamicFields(const QList<Field> &dynamicFields)
{
    mDynamicFields = dynamicFields;

    for (const Field& f : mDynamicFields){

        if (!mIgnoreField.contains(f.name()))
            addColumn(f.name(), DataColumn::typeFromQt(f.type()));

    }
}
}
