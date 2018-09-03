#ifndef VEPANNOTATIONPARSER_H
#define VEPANNOTATIONPARSER_H
#include "abstractannotationparser.h"

namespace cvar{

class VepAnnotationParser : public AbstractAnnotationParser
{
public:
    VepAnnotationParser(const QString& label = "CSQ");

    virtual QList<Field> parseFields(const Field& field);
    virtual QList<Variant> parseVariant(Variant &variant);


protected:

private:
    QList<Field> mAnnFields;

//    const QHash<QString, Field> standardField =
//    {
//        {"allele",           {"allele"       ,"ANN"         ,"reference alllee"            , Field::TEXT}},
//        {"consequence",      {"consequence"  ,"ANN"         ,"consequence"                 , Field::TEXT}},
//        {"symbol",           {"gene_name"    ,"ANN"         ,"name of gene"                , Field::TEXT}},
//        {"gene",             {"gene_id"      ,"ANN"         ,"gene iD"                     , Field::TEXT}},
//        {"impact",           {"impact"       ,"ANN"         ,"impact"                      , Field::TEXT}},
//        {"gnomad_af",        {"gnomad_af"    ,"ANN"         ,"gnomAD allele frequency"     , Field::INTEGER}},

//    };
};

}
#endif // VEPANNOTATIONPARSER_H
