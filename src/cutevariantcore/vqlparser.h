#ifndef VQLCOMPILER_H
#define VQLCOMPILER_H
#include <QtCore>
#include <QRegularExpression>

/*
Exemple of query :
SELECT chr, pos, ref, ann.gene_name FROM variant
SELECT chr, pos, ref, sample["boby"].gt FROM variant
SELECT chr, pos, ref, ann.gene_name FROM variant WHERE pos = 3
SELECT chr, pos, ref, sample["boby"].gt FROM variant INSIDE bed
SELECT chr, pos, genotype("TAZR").GT FROM variant
SELECT chr, pos, phenotype("TAR").malade

*/



class VqlParser
{
public:
    VqlParser(const QString& query = QString());
    const QString query() const;
    const QString tableName() const;
    const QStringList columns() const;
    const QString conditions() const;
    const QString region() const;
    const QStringList samples() const;

    void setQuery(const QString& query);

    bool isValid() const;


protected:



private:
    QString mQuery;

};




#endif // VQLCOMPILER_H
