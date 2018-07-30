#ifndef DEFAULTFIELDS_H
#define DEFAULTFIELDS_H
#include <QHash>
#include "field.h"

namespace cvar {
const QHash<QString, Field> STANDARD_FIELDS =
{
    {"allele",                 {"allele"        ,"ANN"         ,"reference alllele"          , Field::TEXT}},
    {"consequence",            {"consequence"   ,"ANN"         ,"consequence"                , Field::TEXT}},
    {"impact",                 {"impact"        ,"ANN"         ,"name of gene"               , Field::TEXT}},
    {"gene_name",              {"gene_name"     ,"ANN"         ,"gene iD"                    , Field::TEXT}},
    {"gene_id",                {"gene_id"       ,"ANN"         ,"impact"                     , Field::TEXT}},
    {"feature_type",           {"feature_type"  ,"ANN"         ,"impact"                     , Field::TEXT}},
    {"feature_id",             {"feature_id"    ,"ANN"         ,"impact"                     , Field::TEXT}},
    {"biotype",                {"biotype"       ,"ANN"         ,"impact"                     , Field::TEXT}},
    {"hgvs_p",                 {"hgvs_p"        ,"ANN"         ,"impact"                     , Field::TEXT}},
    {"hgvs_c",                 {"hgvs_c"        ,"ANN"         ,"impact"                     , Field::TEXT}},
};


}








#endif // DEFAULTFIELDS_H
