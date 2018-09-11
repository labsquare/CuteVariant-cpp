#ifndef SNPEFFANNOTATIONPARSER_H
#define SNPEFFANNOTATIONPARSER_H
#include "abstractannotationparser.h"
#include "field.h"
#include "variant.h"

namespace cvar{

class SnpEffAnnotationParser : public AbstractAnnotationParser
{
public:
    SnpEffAnnotationParser(const QString& label = "ANN");

    virtual QList<Field> parseFields(const Field& field);
    virtual QList<Variant> parseVariant(Variant &variant);


private:
    QList<Field> mAnnFields;

    const QHash<QString, Field> standardField =
    {
        {"allele",                 {"allele"        ,"ANN"         ,"reference alllee"            , QVariant::String}},
        {"annotation",             {"consequence"   ,"ANN"         ,"consequence"                 , QVariant::String}},
        {"annotation_impact",      {"impact"        ,"ANN"         ,"name of gene"                , QVariant::String}},
        {"gene_name",              {"gene_name"     ,"ANN"         ,"gene iD"                     , QVariant::String}},
        {"gene_id",                {"gene_id"       ,"ANN"         ,"impact"                      , QVariant::String}},
        {"feature_type",           {"feature_type"  ,"ANN"        ,"impact"                      , QVariant::String}},
        {"feature_id",             {"feature_id"    ,"ANN"        ,"impact"                      , QVariant::String}},
        {"transcript_biotype",     {"biotype"       ,"ANN"        ,"impact"                      , QVariant::String}},
        {"hgvs.p",                 {"hgvs_p"       ,"ANN"         ,"impact"                      , QVariant::String}},
        {"hgvs.c",                 {"hgvs_c"       ,"ANN"         ,"impact"                      , QVariant::String}},
        {"cdna_pos / cdna_length", {"dna"       ,"ANN"         ,"impact"                      , QVariant::String}},
        {"cds_pos / cds_length",   {"cds"       ,"ANN"         ,"impact"                      , QVariant::String}},
        {"aa_pos / aa_length",      {"amino"       ,"ANN"         ,"impact"                      , QVariant::String}},
        {"errors / warnings / info", {"info"       ,"ANN"         ,"impact"                      , QVariant::String}},

    };

};


}
#endif // SNPEFFANNOTATIONPARSER_H
