#ifndef SNPEFFANNOTATIONPARSER_H
#define SNPEFFANNOTATIONPARSER_H
#include "abstractannotationparser.h"
#include "field.h"
#include "variant.h"

namespace cvar{

class SnpEffAnnotationParser : public AbstractAnnotationParser
{
public:
    SnpEffAnnotationParser();

    virtual QList<Field> parseFields(const Field& field);
    virtual QList<Variant> parseVariant(Variant &variant);


private:
    QList<Field> mAnnFields;

    const QHash<QString, QString> nameMap =
    {
       {"allele","allele"},
       {"annotation","consequence"},
       {"annotation_impact","impact"},
       {"gene_name","gene_name"},
       {"gene_id","gene_id"},
       {"feature_type","feature_type"},
       {"feature_id","feature_id"},
       {"transcript_biotype","biotype"},
       {"hgvs.p","hgvs_p"},
       {"hgvs.c","hgvs_c"},
       {"cdna_pos / cdna_length", "cdna"},
       {"cds_pos / cds_length", "cds"},
       {"aa_pos / aa_length", "amino"},
       {"errors / warnings / info", "info"}

    };

};


}
#endif // SNPEFFANNOTATIONPARSER_H
