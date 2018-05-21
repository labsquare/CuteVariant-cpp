#ifndef VEPANNOTATIONPARSER_H
#define VEPANNOTATIONPARSER_H
#include "abstractannotationparser.h"

namespace cvar{

class VepAnnotationParser : public AbstractAnnotationParser
{
public:
    VepAnnotationParser();

    virtual QList<Field> parseFields(const Field& field);
    virtual QList<Variant> parseVariant(Variant &variant);


protected:

private:
    QList<Field> mAnnFields;

    const QHash<QString, QString> nameMap =
    {
       {"allele","allele"},
       {"consequence","consequence"},
       {"impact","impact"},
       {"symbol","gene_name"},
       {"gene","gene_id"},
       {"feature_type","feature_type"},
       {"feature","feature_id"},
       {"biotype","biotype"},
       {"hgvsp","hgvs_p"},
       {"hgvsc","hgvs_c"}

    };
};

}
#endif // VEPANNOTATIONPARSER_H
